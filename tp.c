#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"
#include "socketTDA.h"

int write_chunk(FILE* pFile, unsigned char* buffer, size_t length) {
  return fwrite(buffer, 1, length, pFile);
}

int read_chunk(FILE *pFile, unsigned char* buf, int length) {
  return fread(buf, 1, length, pFile);
}

void run_client(const char* port, const char* host, const char* key,
  const char* filename);
void run_server(const char* port, const char* key);

int main(int argc, char const *argv[]) {
  if (strncmp(argv[1], "server", 6) == 0) {
    run_server(argv[2], argv[3]);
  } else if (strncmp(argv[1], "client", 6) == 0) {
    run_client(argv[3], argv[2], argv[4], argv[5]);
  } else {
    printf("Parámetros incorrectos.\n");
    return 1;
  }
  return 0;
}

void run_client(const char* port, const char* host, const char* key,
                const char* filename) {
  cipher_t cipher;
  socket_t sock;
  FILE* infile;
  unsigned char buffer[65], encrypted[65];
  int r, size = 65;
  //initialize structures
  if (cipher_init(&cipher, key, strlen(key)) != 0)
    exit(2);
  if (socket_create(&sock) != 0)
    exit(2);
  memset(buffer, 0, 65);
  memset(encrypted, 0, 65);
  //initialize output files
  if ((infile = fopen(filename,"rb")) == NULL) {
    exit(2);
  }
  //connect to server
  socket_connect(&sock, host, port);

  //read from file, encrypt and send to server
  while ((r = read_chunk(infile, buffer, size)) > 0) {
    cipher_encrypt(&cipher, buffer, encrypted, r);
    socket_send(&sock, r, encrypted);
  }
  //cipher_encrypt(&cipher, buffer, encrypted, size);
  //socket_send(&sock, size, buffer);
  //close file
  fclose(infile);
  //free resources
  cipher_destroy(&cipher);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}

void run_server(const char* port, const char* key) {
  cipher_t cipher;
  socket_t sock, new_sock;
  FILE* outfile;
  unsigned char buffer[50], decrypted[50];
  int s, size = 50;
  //initialize structures
  if (cipher_init(&cipher, key, strlen(key)) != 0)
    exit(2);
  if (socket_create(&sock) != 0)
    exit(2);
  memset(buffer, 0, 50);
  memset(decrypted, 0, 50);  //initialize output files
  if ((outfile = fopen("out","wb")) == NULL) {
    exit(2);
  }
  //bind socket and wait client
  socket_bind_and_listen(&sock, port);
  socket_accept(&sock, &new_sock);

  //receive encrypted stream, decrypt it and write it
  while ((s = socket_receive(&new_sock, size, buffer)) > 0) {
    cipher_decrypt(&cipher, buffer, decrypted, s);
    write_chunk(outfile, decrypted, s);
  }
  //cipher_decrypt(&cipher, buffer, decrypted, s);
  //write_chunk(outfile, decrypted, s);
  //close file
  fclose(outfile);
  //free resources
  cipher_destroy(&cipher);
  socket_shutdown(&new_sock);
  socket_destroy(&new_sock);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}
