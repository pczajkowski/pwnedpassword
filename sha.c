#include "sha.h"

static unsigned char *generateHash(const char *string, size_t length) {
	unsigned char *hash = malloc(SHA_DIGEST_LENGTH);
	if (hash == NULL) {
		puts("Couldn't allocate memory for hash!");
		return NULL;
	}
	
	SHA1((unsigned char*)string, length, hash);

	return hash;
}

static char *hashToString(unsigned char *hash) {
	char *string = malloc(2 * SHA_DIGEST_LENGTH + 1);
	if (string == NULL) {
		puts("Couldn't allocate memory for string!");
		return NULL;
	}

	for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
		sprintf(string+(i*2), "%02X", hash[i]);

	return string;
}

char *getHash(const char *string) {
	size_t length = strlen(string);
	unsigned char *hash = generateHash(string, length);
	if (hash == NULL) {
		puts("Couldn't generate hash!");
		return NULL;
	}
	
	char *hashString = hashToString(hash);
	if (hashString == NULL) {
		puts("Couldn't convert hash to string!");
		return NULL;
	}
	
	free(hash);

	return hashString;
}

