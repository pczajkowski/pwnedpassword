#include <ctype.h>
#include "curl.h"
#include "sha.h"

// https://haveibeenpwned.com/API/v2#SearchingPwnedPasswordsByRange

#define HASH_PREFIX_SIZE 5
#define HASH_SUFFIX_SIZE 35
#define URL_SIZE 43

char *getURL(const char* hash) {
	const char *baseURL = "https://api.pwnedpasswords.com/range/";
	char *url = calloc(URL_SIZE, 1);
	strncpy(url, baseURL, strlen(baseURL));
	strncat(url, hash, HASH_PREFIX_SIZE);

	return url;
}

char *getSuffixUppercase(const char *hash) {
	char hashSuffix[HASH_SUFFIX_SIZE + 1];
	strncpy(hashSuffix, hash+HASH_PREFIX_SIZE, HASH_SUFFIX_SIZE);

	char *suffixUpper = malloc(HASH_SUFFIX_SIZE + 1);
	if (suffixUpper == NULL) {
		puts("Couldn't allocate memory for suffix!");
		return NULL;
	}
	
	for (int i = 0; i < HASH_SUFFIX_SIZE; i++) {
		int c = hashSuffix[i];
		c = toupper(c);
		sprintf(suffixUpper+i, "%c", c);
	}

	return suffixUpper;
}

void printNumber(const char *data) {
	for (int i = 0; data[i] != '\n'; i++)
		putchar(data[i]);
	putchar('\n');
}

int findSuffix(const char *suffix, const char *data) {
	for (int i = 0; data[i] != 0; i++) {
		int j;
		for (j = 0; suffix[j] != 0; j++)
			if (data[i+j] != suffix[j])
				break;

		if (suffix[j] == 0 && data[i+j] == ':') {
			printf("This is how many times your password was pwned: ");
			printNumber(data+i+j+1);
			return 1;
		}
	}
	return 0;
}

void usage(const char *app) {
	printf("Usage:\n%s <password>\n", app);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	char *hash = getHash(argv[1]);
	if (hash == NULL) {
		puts("Couldn't get hash!");
		return 1;
	}
	
	char *url = getURL(hash);
	char *suffix = getSuffixUppercase(hash);
	if (suffix == NULL) {
		puts("Couldn't make suffix uppercase!");
		return 1;
	}
	
	free(hash);

	char *data = getData(url);
	if (data == NULL) {
		puts("Couldn't get data from the API!");
		return 1;
	}
	
	free(url);

	if (!findSuffix(suffix, data)) puts("Password not pwned!");

	free(data);
	free(suffix);
}
