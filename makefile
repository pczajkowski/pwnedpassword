CFLAGS=-Wall -Wextra -Wshadow -O3 -std=c99
LDLIBS=-lcurl -lcrypto
objects=curl.o sha.o

pwned: $(objects)

.PHONY: clean
clean:
	rm *.o

default: pwned
