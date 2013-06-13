CFLAGS+=-g

.PHONY: test_all

test_all: read cmp_kongstr

read: read.c
	$(CC) $(CFLAGS) -o $@ $^

splitstr: splitstr.c
	$(CC) $(CFLAGS) -o $@ $^

cmp_kongstr: cmp_kongstr.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm read split_str