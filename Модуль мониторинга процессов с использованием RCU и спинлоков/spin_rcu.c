#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/spinlock.h>
#include <linux/rcupdate.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/delay.h>

struct task_info
{
    pid_t pid;
    char comm[TASK_COMM_LEN];
    int state;
    struct list_head list;
    struct rcu_head rcu;
};

static LIST_HEAD(task_list);
static DEFINE_SPINLOCK(task_list_lock);
static struct task_struct *monitor_thread;

static void update_task_list(void)
{
    struct task_struct *task;
    struct task_info *info, *tmp;

    spin_lock(&task_list_lock);
    list_for_each_entry_safe(info, tmp, &task_list, list)
    {
        list_del_rcu(&info->list);
        kfree_rcu(info, rcu);
    }
    spin_unlock(&task_list_lock);

    rcu_read_lock();
    for_each_process(task)
    {
        info = kmalloc(sizeof(*info), GFP_ATOMIC);
        if (!info)
            continue;

        info->pid = task->pid;
        strncpy(info->comm, task->comm, TASK_COMM_LEN);
        info->state = task->__state;

        spin_lock(&task_list_lock);
        list_add_rcu(&info->list, &task_list);
        spin_unlock(&task_list_lock);
    }
    rcu_read_unlock();
}

static int task_monitor_show(struct seq_file *m, void *v)
{
    struct task_info *info;

    rcu_read_lock();
    list_for_each_entry_rcu(info, &task_list, list)
    {
        seq_printf(m, "PID: %d, Name: %s, State: %d\n", info->pid, info->comm, info->state);
    }
    rcu_read_unlock();

    return 0;
}

static int task_monitor_open(struct inode *inode, struct file *file)
{
    return single_open(file, task_monitor_show, NULL);
}

static const struct proc_ops task_monitor_fops =
{
    .proc_open = task_monitor_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int monitor_thread_fn(void *data)
{
    while (!kthread_should_stop())
    {
        update_task_list();
        ssleep(1);
    }
    return 0;
}

static int __init task_monitor_init(void)
{
    proc_create("task_monitor", 0, NULL, &task_monitor_fops);

    monitor_thread = kthread_run(monitor_thread_fn, NULL, "task_monitor");
    if (IS_ERR(monitor_thread))
    {
        pr_err("Не удалось запустить поток мониторинга задач\n");
        return PTR_ERR(monitor_thread);
    }

    pr_info("Модуль мониторинга задач загружен\n");
    return 0;
}

static void __exit task_monitor_exit(void)
{
    struct task_info *info, *tmp;

    if (monitor_thread)
        kthread_stop(monitor_thread);

    remove_proc_entry("task_monitor", NULL);

    spin_lock(&task_list_lock);
    list_for_each_entry_safe(info, tmp, &task_list, list)
    {
        list_del_rcu(&info->list);
        kfree_rcu(info, rcu);
    }
    spin_unlock(&task_list_lock);

    pr_info("Модуль мониторинга задач выгружен\n");
}

void get_task_list(void)
{
    update_task_list();
}
EXPORT_SYMBOL(get_task_list);

module_init(task_monitor_init);
module_exit(task_monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WARG");
MODULE_DESCRIPTION("Модуль мониторинга задач с использованием RCU и спинлоков");
