#ifndef CIPHER_H
#define CIPHER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Cipher {
  unsigned char S[256];
  int i,j;
} cipher_t;

int cipher_init(cipher_t* c, char* key, int keylength);
int cipher_get_keystream(cipher_t* c, size_t length, unsigned char* keystream);
int cipher_decrypt(cipher_t* c, unsigned char* original, unsigned char* decrypted, size_t length);
int cipher_encrypt(cipher_t* c, unsigned char* original, unsigned char* encrypted, size_t length);
int cipher_destroy(cipher_t* c);

#endif
