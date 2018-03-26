#include <stdio.h>
#include <stdlib.h>

#include "cipher.h"

int write_hexa_file(FILE* pFile, unsigned char* text, size_t length) {
  return fwrite(buffer, 1, length, pFile);
}

int read_chunk(FILE *pFile, unsigned char* buf, int length) {
  //TODO: ver si fread lee de una cantidad length
  return fread(buf, 1, length, pFile);
}

int main(int argc, char const *argv[]) {
  
  return 0;
}
