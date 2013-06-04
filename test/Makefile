CFLAGS+=-g

.PHONY: test_all

test_all: read splitstr

read: read.c
	$(CC) $(CFLAGS) -o $@ $^

splitstr: splitstr.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm read split_str