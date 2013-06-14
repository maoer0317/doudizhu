CC=gcc
CFLAGS=-Wall
MAKE=make
DEBUG=y

export 

ifeq ($(DEBUG),y)
   CFLAGS+= -g
else
   CFLAGS+= -O2
endif

SUBDIRS=test

.PHONY: all for_test

all: subdirs for_test play_cards

for_test: cards_test cards_f_test

cards_test: cards.o cards_test.o
	@echo 
	$(CC) $(CFLAGS) -o $@ $^ 

cards_f_test: cards.o cards_f.o cards_f_test.o
	@echo 
	$(CC) $(CFLAGS) -o $@ $^ 

play_cards: cards.o cards_f.o and_or_tree.o play_cards.o
	$(CC) $(CFLAGS) -o $@ $^

subdirs:
#@echo $(CFLAGS)
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
	-rm cards_test cards_f_test play_cards *.o