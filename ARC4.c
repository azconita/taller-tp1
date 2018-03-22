#include <stdio.h>


int* KSA(unsigned char *key, int keylength) {
  int i, j, k;
  unsigned char S[256];
  for (i = 0; i < 256; i++) {
    S[i] = i;
  }
  for (i = 0; i < 256; i++) {
    j = (j + S[i] + key[i % keylength]) % 256;
    k = S[i];
    S[i] = S[j];
    S[j] = k;
  }
  return S;
}

int PRGA(int S[256]) {
  int i = 0;
  int j = 0;
  unsigned char k, K;

  i = (i + 1) % 256;
  j = (j + S[i]) % 256;
  k = S[i];
  S[i] = S[j];
  S[j] = k;
  K = S[(S[i] + S[j]) % 256]
  return K;
}

void cipher(unsigned char S[256], unsigned char *input,) {
  output[i] := PRGA() ^ input[i]
}
