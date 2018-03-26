#include <stdio.h>
#include <stdlib.h>

#include "cipher.h"

int read_input_file(const char* filename, unsigned char* buf);
int print_hexa(unsigned char* text, size_t length);

void test_cipher2();
void test_cipher_file(const char* filename);
int main(int argc, char const *argv[]) {
  test_cipher_file(argv[1]);
  return 0;
}

int print_hexa(unsigned char* text, size_t length) {
  size_t i;
  for (i = 0; i < length; i++) {
    printf("%x", text[i]);
  }
  printf("\n");
}


int read_input_file(const char* filename, unsigned char* buf) {
  FILE *fp_input;
  size_t nread;
  fp_input = fopen(filename, "rb");
  if (fp_input) {
    /*while ((nread = fread(buf, 1, sizeof buf, fp_input)) > 0) {
      fwrite(buf, 1, nread, stdout);
    }*/
    nread = fread(buf, 1, 13, fp_input);
    fclose(fp_input);
  }
  return nread;
}


void test_cipher() {
    unsigned char buf[64], keystream[5];
    cipher_t cipher;
    int keylength;
    char key[8] = "secreto";
    keylength = 7;
    cipher_init(&cipher, key, keylength);
    printf("%d %d %d %d %d\n",cipher.S[0], cipher.S[1], cipher.S[2], cipher.S[3], cipher.S[4]);
    cipher_get_keystream(&cipher, 4, keystream);
    printf("%d %d %d %d\n", keystream[0], keystream[1], keystream[2], keystream[3]);
}

void test_cipher2() {
  unsigned char encrypted[10], keystream[10];
  cipher_t cipher;
  int keylength;
  char txt[10] = "Plaintext";
  char key[8] = "Key";
  keylength = 3;
  cipher_init(&cipher, key, keylength);
  cipher_get_keystream(&cipher, 9, keystream);
  printf("keystream:\n");
  print_hexa(keystream, 9);
  //cipher_encrypt(&cipher, txt, encrypted, 9);
  //printf("encrypt:\n");
  //print_hexa(encrypted, 9);
}

void test_cipher_file(const char *filename) {
    unsigned char buf[64], encrypted[64];
    cipher_t cipher;
    int keylength, readed;
    char key[8] = "Key";
    keylength = 3;
    cipher_init(&cipher, key, keylength);
    readed = read_input_file(filename, buf);
    print_hexa(buf, readed);
    printf("%d\n", readed);
    cipher_encrypt(&cipher, buf, encrypted, readed);
    printf("encrypt:\n");
    print_hexa(encrypted, readed);
}
