CFLAGS=-g -Wall -Wextra -O3 -std=gnu99
LDLIBS=-lcurl -lssl -lcrypto
objects=curl.o sha.o

pwned: $(objects)

.PHONY: clean
clean:
	rm *.o

default: pwned
