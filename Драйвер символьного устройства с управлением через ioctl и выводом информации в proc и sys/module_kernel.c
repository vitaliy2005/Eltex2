#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/kobject.h>
#include <linux/seq_file.h>
#include "mod_kernel.h"

static int32_t major_number;
static struct class* custom_class = NULL;
static DEFINE_MUTEX(custom_mutex);
static char *buffer = NULL;
static int32_t buffer_size = 1024;
static struct kobject *custom_kobj = NULL;
static int device_open(struct inode* inode, struct file* file)
{
    if (!mutex_trylock(&custom_mutex))
    {
        printk(KERN_ERR "Device is busy\n");
        return -EBUSY;
    }
    printk(KERN_INFO "Device opened\n");

    return 0;
}

static int device_release(struct inode* inode, struct file* file)
{
    mutex_unlock(&custom_mutex);
    printk(KERN_INFO "Device closed\n");

    return 0;
}

static ssize_t device_read(struct file* file, char __user* user_buffer, size_t count, loff_t* offset)
{
    int len = strlen(buffer);
    if (*offset >= len) return 0;
    if (count > len - *offset) count = len - *offset;
    if (copy_to_user(user_buffer, buffer + *offset, count)) return -EFAULT;
    *offset += count;
    return count;
}

static ssize_t device_write(struct file* file, const char __user* user_buffer, size_t count, loff_t* offset)
{
    if (count > buffer_size) return -EINVAL;
    if (copy_from_user(buffer, user_buffer, count)) return -EFAULT;
    buffer[count] = '\0';
    return count;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int state;
    switch (cmd)
    {
        case IOCTL_SET_STATE:
            if (copy_from_user(&state, (int __user *)arg, sizeof(state)))
                return -EFAULT;
            printk(KERN_INFO "State set to: %d\n", state);
            break;
        case IOCTL_GET_STATE:
            state = 42;
            if (copy_to_user((int __user *)arg, &state, sizeof(state)))
                return -EFAULT;
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
};

static struct proc_dir_entry *proc_entry;

static int proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Device state: %s\n", buffer);
    return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_show, NULL);
}

static const struct proc_ops proc_fops =
{
    .proc_open    = proc_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

static ssize_t sysfs_show(struct kobject* kobj, struct kobj_attribute* attr, char *buf)
{
    return sprintf(buf, "%s\n", buffer);
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    strncpy(buffer, buf, buffer_size);
    buffer[buffer_size - 1] = '\0';
    return count;
}

static struct kobj_attribute custom_attr = __ATTR(custom_attr, 0664, sysfs_show, sysfs_store);

static struct attribute* attrs[] =
{
    &custom_attr.attr,
    NULL,
};

static struct attribute_group attr_group =
{
    .attrs = attrs,
};

static int __init custom_device_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0)
    {
        printk(KERN_ERR "Failed to register a major number\n");
        return major_number;
    }

    custom_class = class_create(CLASS_NAME);
    if (IS_ERR(custom_class))
    {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ERR "Failed to register device class\n");
        return PTR_ERR(custom_class);
    }

    device_create(custom_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);

    buffer = kmalloc(buffer_size, GFP_KERNEL);
    if (!buffer)
    {
        device_destroy(custom_class, MKDEV(major_number, 0));
        class_destroy(custom_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return -ENOMEM;
    }

    proc_entry = proc_create("custom_device_info", 0, NULL, &proc_fops);
    if (!proc_entry)
    {
        kfree(buffer);
        device_destroy(custom_class, MKDEV(major_number, 0));
        class_destroy(custom_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return -ENOMEM;
    }

    if (custom_kobj)
    {
        kobject_put(custom_kobj);
        custom_kobj = NULL;
    }

    custom_kobj = kobject_create_and_add(DEVICE_NAME, kernel_kobj->parent);
    if (!custom_kobj)
    {
        proc_remove(proc_entry);
        kfree(buffer);
        device_destroy(custom_class, MKDEV(major_number, 0));
        class_destroy(custom_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return -ENOMEM;
    }

    if (sysfs_create_group(custom_kobj, &attr_group))
    {
        kobject_put(custom_kobj);
        proc_remove(proc_entry);
        kfree(buffer);
        device_destroy(custom_class, MKDEV(major_number, 0));
        class_destroy(custom_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return -ENOMEM;
    }

    printk(KERN_INFO "Custom device driver loaded\n");
    return 0;
}

static void __exit custom_device_exit(void)
{
    device_destroy(custom_class, MKDEV(major_number, 0));
    class_destroy(custom_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    kfree(buffer);
    proc_remove(proc_entry);
    if (custom_kobj)
    {
        kobject_put(custom_kobj);
        custom_kobj = NULL;
    }
    printk(KERN_INFO "Custom device driver unloaded\n");
}

module_init(custom_device_init);
module_exit(custom_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WARG");
