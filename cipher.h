#ifndef CIPHER_T
#define CIPHER_T value

#include <stdlib.h>

struct cipher_t {
  unsigned char S[256];
  int x,y;
} typedef cipher_t;

int cipher_init(cipher_t* c, char* key, int keylength);
int cipher_get_keystream(cipher_t* c, size_t length, char* keystream);
int cipher_encrypt(cipher_t* c, char* original, char* encrypted);
int cipher_decrypt(cipher_t* c, char* original, char* decrypted);
int cipher_destroy(cipher_t* c);

#endif
