#include <ctype.h>
#include "curl.h"
#include "sha.h"

// https://haveibeenpwned.com/API/v2#SearchingPwnedPasswordsByRange

#define HASH_PREFIX_SIZE 5
#define HASH_SUFFIX_SIZE 35
#define URL_SIZE 43

char *getURL(char* hash) {
	const char *baseURL = "https://api.pwnedpasswords.com/range/";
	char *url = calloc(URL_SIZE, 1);
	strncpy(url, baseURL, strlen(baseURL));
	strncat(url, hash, HASH_PREFIX_SIZE);

	return url;
}

char *getSuffixUppercase(char *hash) {
	char hashSuffix[HASH_SUFFIX_SIZE + 1];
	strncpy(hashSuffix, hash+HASH_PREFIX_SIZE, HASH_SUFFIX_SIZE);

	char *suffixUpper = malloc(HASH_SUFFIX_SIZE + 1);
	for (int i = 0; i < HASH_SUFFIX_SIZE; i++) {
		int c = hashSuffix[i];
		if (islower(c)) c = toupper(c);
		sprintf(suffixUpper+i, "%c", c);
	}

	return suffixUpper;
}

int findSuffix(char *suffix, char *data) {
	int found = 0;
	int check = 1;

	int suffixCount = 0;
	for (unsigned long i = 0; i < strlen(data); i++) {
		if (found) {
			putchar(data[i]);
			if (data[i] == '\n') return found;
		}

		if (check) {
			if (data[i] == ':') {
				puts("This is how many times your password was pwned:");
				found = 1;
			}
			if (suffix[suffixCount] != data[i]) check = 0;
			suffixCount++;
		}

		if (data[i] == '\n') {
			check = 1;
			suffixCount = 0;
		}
	}
	return found;
}

void usage(char *app) {
	printf("Usage:\n%s <password>\n", app);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	char *hash = getHash(argv[1]);
	char *url = getURL(hash);
	char *suffix = getSuffixUppercase(hash);
	free(hash);

	char *data = getData(url);
	free(url);

	if (!findSuffix(suffix, data)) puts("Password not pwned!");
	
	free(data);
	free(suffix);
}
