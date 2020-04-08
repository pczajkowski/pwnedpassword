#include <ctype.h>
#include "curl.h"
#include "sha.h"

// https://haveibeenpwned.com/API/v2#SearchingPwnedPasswordsByRange

#define HASH_PREFIX_LENGTH 5
#define HASH_SUFFIX_LENGTH 35

#define BASEURL "https://api.pwnedpasswords.com/range/"
#define BASEURL_SIZE (sizeof BASEURL)
#define URL_SIZE (BASEURL_SIZE + HASH_PREFIX_LENGTH)

#define NUMBER_SIZE 20

char *getURL(const char* hash) {
	char *url = malloc(URL_SIZE);
	if (url == NULL) return NULL;

	snprintf(url, URL_SIZE, "%s%s", BASEURL, hash);

	return url;
}

char *getNumber(char *text) {
	char *part = strchr(text, ':');
	if (part == NULL) return NULL;

	char *number = malloc(NUMBER_SIZE);
	snprintf(number, NUMBER_SIZE, "%s", part+1);
	return number;
}

char *findSuffix(const char *suffix, char *data) {
	char *token = strtok(data, "\n");

	while (token != NULL) {
		if (strncmp(token, suffix, HASH_SUFFIX_LENGTH) == 0) {
			return token;
		}

		token = strtok(NULL, "\n");
	}

	return NULL;
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

	char *data = getData(url);
	if (data == NULL) {
		puts("Couldn't get data from the API!");
		return 1;
	}

	free(url);

	char *suffix = findSuffix(hash+HASH_PREFIX_LENGTH, data);
	if (suffix == NULL) {
		puts("Password not pwned!");
		return 1;
	}

	char *number = getNumber(suffix);
	if (number == NULL) {
		puts("Hash found, but can't obtain the number!");
		return 1;
	}

	printf("This is how many times your password was pwned: %s\n", number);

	free(hash);
	free(data);
	free(number);
}
