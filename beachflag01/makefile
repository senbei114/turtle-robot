PROJECT = beachflag01

TOOLDIR=C:/Devz/gcc4mbed
MAKEDIR=C:/Devz/gnuwin32
GCC4MBED_DIR=$(TOOLDIR)
LPC_DEPLOY=$(TOOLDIR)/pnotepad/copytombed.bat

LIBS_PREFIX=
LIBS_SUFFIX=


export PATH=C:/Windows/system32;C:/Windows;$(TOOLDIR)/arm-2011.03/bin;$(MAKEDIR)/bin
include $(GCC4MBED_DIR)/build/gcc4mbed.mk

write : deploy

.PHONY :  write all deploy
