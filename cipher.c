#include "cipher.h"

int KSA(unsigned char S[256], unsigned char *key, int keylength);

int cipher_init(cipher_t* c, char* key, int keylength){
  if (KSA(c->S,(unsigned char *) key, keylength) != 0)
    exit(2);
  c->x = 0;
  c->y = 0;
  return 0;
}
int cipher_get_keystream(cipher_t* c, size_t length, char* keystream) {
  int i, k;
  for (i = 0; i < length; i++) {
    PRGA(c->S, c->x, c->j);
  }
}
int cipher_encrypt(cipher_t* c, char* original, char* encrypted);
int cipher_decrypt(cipher_t* c, char* original, char* decrypted);
int cipher_destroy(cipher_t* c);


int KSA(unsigned char S[256], unsigned char *key, int keylength) {
  int i, k, j = 0;
  for (i = 0; i < 256; i++) {
    S[i] = i;
  }
  for (i = 0; i < 256; i++) {
    j = (j + S[i] + key[i % keylength]) % 256;
    k = S[i];
    S[i] = S[j];
    S[j] = k;
  }
  return 0;
}

int PRGA(int S[256], int i, int j) {
  unsigned char k, K;

  i = (i + 1) % 256;
  j = (j + S[i]) % 256;
  k = S[i];
  S[i] = S[j];
  S[j] = k;
  K = S[(S[i] + S[j]) % 256]
  return K;
}
