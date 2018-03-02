CFLAGS=-g -Wall -Wextra -O3 -std=gnu99
LDLIBS=-lcurl -lssl -lcrypto
objects=curl.o sha.o

password: $(objects)

.PHONY: clean
clean:
	rm *.o

default: password
