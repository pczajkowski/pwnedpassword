CFLAGS=-Wall -Wextra -Wshadow -O3 -std=gnu99
LDLIBS=-lcurl -lssl -lcrypto
objects=curl.o sha.o
mingwCFLAGS=-Wall -Wextra -O3 -std=gnu99
mingwLDLIBS=-lcurl -lssl -lcrypto
mingw=x86_64-w64-mingw32-gcc

pwned: $(objects)

.PHONY: clean
clean:
	rm *.o

default: pwned

win/pwned.exe:
	$(mingw) $(mingwCFLAGS) -c curl.c $(mingwLDLIBS)
	$(mingw) $(mingwCFLAGS) -c sha.c $(mingwLDLIBS)
	$(mingw) $(mingwCFLAGS) pwned.c $(objects) $(mingwLDLIBS) -o $@

win: win/pwned.exe
