CC=gcc
OBJS=test.o csv.o
CFLAGS+=-pthread
LDFLAGS+=-pthread

test:$(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

csv.o:csv.c
	$(CC) $^ $(CFLAGS) -c -o $@
test.o:test.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	$(RM) *.o test
