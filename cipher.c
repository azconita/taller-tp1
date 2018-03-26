#include "cipher.h"

int KSA(unsigned char S[256], unsigned char *key, int keylength);
unsigned char PRGA(cipher_t* c);
void cipher(cipher_t* c, unsigned char *input, unsigned char *output, size_t length);

int cipher_init(cipher_t* c, char* key, int keylength){
  if (KSA(c->S,(unsigned char *) key, keylength) != 0)
    exit(2);
  c->i = 0;
  c->j = 0;
  return 0;
}
int cipher_get_keystream(cipher_t* c, size_t length, unsigned char* keystream) {
  int i, k;
  for (i = 0; i < length; i++) {
    keystream[i] = PRGA(c);
  }
  return 0;
}
int cipher_encrypt(cipher_t* c, unsigned char* original, unsigned char* encrypted, size_t length) {
  cipher(c, original, encrypted, length);
}

int cipher_decrypt(cipher_t* c, unsigned char* original, unsigned char* decrypted, size_t length) {
  cipher(c, original, decrypted, length);
}

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

unsigned char PRGA(cipher_t* c) {
  unsigned char k, K;

  c->i = (c->i + 1) % 256;
  c->j = (c->j + c->S[c->i]) % 256;
  k = c->S[c->i];
  c->S[c->i] = c->S[c->j];
  c->S[c->j] = k;
  K = c->S[(c->S[c->i] + c->S[c->j]) % 256];
  return K;
}

void cipher(cipher_t* c, unsigned char *input, unsigned char *output, size_t length) {
  size_t i;
  unsigned char keystream[length];
  cipher_get_keystream(c, length, keystream);
  for (i = 0; i < length; i++) {
    output[i] = keystream[i] ^ input[i];
  }
}
