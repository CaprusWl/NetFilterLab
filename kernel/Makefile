MODULE_NAME := NetFireWallModule

obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-objs := \
	src/NetLinkMsgHandler.o \
       	src/NetFireWall.o \
       	src/Filter.o \
       	src/Connection.o \
	src/Datagram.o \
       	src/Logger.o \
       	src/Utils.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all: mod

mod:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -fr .*.cmd *.ko *.o *.cmd $(MODULE_NAME).mod $(MODULE_NAME).mod.c modules.order Module.symvers
	cd src && rm -fr .*.cmd *.ko *.o *.cmd $(MODULE_NAME).mod $(MODULE_NAME).mod.c modules.order Module.symvers

