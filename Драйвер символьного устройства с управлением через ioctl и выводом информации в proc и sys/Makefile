obj-m += module_kernel.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc main.c -o main
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm main
