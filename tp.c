#include <stdio.h>
#include <stdlib.h>

#include "cipher.h"

int read_input_file(const char* filename, unsigned char* buf);

int main(int argc, char const *argv[]) {
  unsigned char buf[64];
  cipher_t cipher;
  int keylength;
  char key[8] = "secreto";
  keylength = 7;
  cipher_init(&cipher, key, keylength);
  printf("%d %d %d %d %d\n", cipher.S[0], cipher.S[1], cipher.S[2], cipher.S[3], cipher.S[4]);
  read_input_file(argv[1], buf);
  //cipher_destroy();
  return 0;
}


int read_input_file(const char* filename, unsigned char* buf) {
  FILE *fp_input;
  size_t nread;
  fp_input = fopen(filename, "rb");
  if (fp_input) {
    while ((nread = fread(buf, 1, sizeof buf, fp_input)) > 0) {
      fwrite(buf, 1, nread, stdout);
    }
    fclose(fp_input);
  }
  return nread;
}
