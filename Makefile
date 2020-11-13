MODULE_NAME := NetFireWallModule

obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-objs := NetLinkMsgHandler.o NetFireWall.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all: mod app

mod:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

app:
	gcc -o nltest_uapp nltest_uapp.c

clean:
	rm -fr .*.cmd *.ko *.o *.cmd nltest_uapp $(MODULE_NAME).mod $(MODULE_NAME).mod.c modules.order Module.symvers

