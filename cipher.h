#ifndef CIPHER_T
#define CIPHER_T value

#include <stdlib.h>
#include <stdio.h>

struct cipher_t {
  unsigned char S[256];
  int i,j;
} typedef cipher_t;

int cipher_init(cipher_t* c, char* key, int keylength);
int cipher_get_keystream(cipher_t* c, size_t length, unsigned char* keystream);
int cipher_decrypt(cipher_t* c, unsigned char* original, unsigned char* decrypted, size_t length);
int cipher_encrypt(cipher_t* c, unsigned char* original, unsigned char* encrypted, size_t length);
int cipher_destroy(cipher_t* c);

#endif
