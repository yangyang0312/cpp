CC = gcc
RM = rm

CFLAGS=$(FLAG)
CFLAGS +=-g -Wall

TARGETS := hello

all:$(TARGETS)

$(TARGETS):hello.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	-$(RM) -f *.o
	-$(RM) -f $(TARGETS)
