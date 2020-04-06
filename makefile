CFLAGS=-Wall -Wextra -Wshadow -O3 -std=c99
LDLIBS=-L/usr/local/opt/openssl@1.1/lib -lcurl -lcrypto
objects=curl.o sha.o

pwned: $(objects)

.PHONY: clean
clean:
	rm *.o

default: pwned
