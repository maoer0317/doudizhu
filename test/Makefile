CFLAGS+=-g

.PHONY: test_all

test_all: read cmp_kongstr enum_test

read: read.c
	$(CC) $(CFLAGS) -o $@ $^

splitstr: splitstr.c
	$(CC) $(CFLAGS) -o $@ $^

cmp_kongstr: cmp_kongstr.c
	$(CC) $(CFLAGS) -o $@ $^

#enum_test: enum_test.o

clean:
	-rm read splitstr cmp_kongstr enum_test