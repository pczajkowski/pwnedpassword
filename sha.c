#include "sha.h"

static unsigned char *generateHash(char *string, size_t length) {
	unsigned char *hash = malloc(SHA_DIGEST_LENGTH);
	SHA1((unsigned char*)string, length, hash);

	return hash;
}

static char *hashToString(unsigned char *hash) {
	char *string = malloc(2 * SHA_DIGEST_LENGTH + 1);

	for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
		sprintf(string+(i*2), "%02x", hash[i]);

	return string;
}

char *getHash(char *string) {
	size_t length = strlen(string);
	unsigned char *hash = generateHash(string, length);
	char *hashString = hashToString(hash);
	free(hash);

	return hashString;
}

