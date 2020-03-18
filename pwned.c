#include <ctype.h>
#include "curl.h"
#include "sha.h"

// https://haveibeenpwned.com/API/v2#SearchingPwnedPasswordsByRange

#define HASH_PREFIX_LENGTH 5
#define HASH_PREFIX_SIZE 6

#define HASH_SUFFIX_LENGTH 35
#define HASH_SUFFIX_SIZE 36

#define URL_SIZE 43
#define BASEURL_SIZE 38

char *getURL(const char* hash) {
	const char *baseURL = "https://api.pwnedpasswords.com/range/";
	char *url = malloc(URL_SIZE);
	if (url == NULL) return NULL;

	strncpy(url, baseURL, BASEURL_SIZE);
	strncat(url, hash, HASH_PREFIX_LENGTH);

	return url;
}

char *getSuffixUppercase(const char *hash) {
	char hashSuffix[HASH_SUFFIX_SIZE];
	strcpy(hashSuffix, hash+HASH_PREFIX_LENGTH);

	char *suffixUpper = malloc(HASH_SUFFIX_SIZE);
	if (suffixUpper == NULL) {
		puts("Couldn't allocate memory for suffix!");
		return NULL;
	}

	for (int i = 0; i < HASH_SUFFIX_LENGTH; i++) {
		int c = hashSuffix[i];
		c = toupper(c);
		sprintf(suffixUpper+i, "%c", c);
	}
	suffixUpper[HASH_SUFFIX_LENGTH] = 0;

	return suffixUpper;
}

int findSuffix(const char *suffix, const char *data) {
	char *token, *string, *tofree;
	tofree = string = strdup(data);

	while ((token = strsep(&string, "\n")) != NULL) {
		if (strncmp(token, suffix, HASH_SUFFIX_LENGTH) == 0) {
			char *part = strsep(&token, ":");

			if (part != NULL) {
				printf("This is how many times your password was pwned: %s\n", token);
				free(tofree);
				return 1;
			}

			puts("Hash found, but can't obtain the number!");
			break;
		}
	}

	free(tofree);

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
	if (url == NULL) {
		puts("Couldn't get URL!");
		return 1;
	}

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
