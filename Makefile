CC=gcc
FLAGS=-Wall
MAKE=make
DEBUG=y

ifeq ($(DEBUG),y)
   CFLAGS+= -g
else
   CFLAGS+= -O2
endif

SUBDIRS=test

.PHONY: all

all: subdirs

subdirs:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
