#
# Makefile for kernel test
#
PWD := $(shell pwd) 
KVERSION  := $(shell uname -r)
KERNEL_DIR  = /usr/src/linux-headers-$(KVERSION)/

MODULE_NAME  = m_fixmap
obj-m  := $(MODULE_NAME).o  

all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean