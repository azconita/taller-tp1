#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"
#include "socketTDA.h"

void run_client(const char* port, const char* host, const char* key,
  const char* filename);
void run_server(const char* port, const char* key, const char* filename);

int main(int argc, char const *argv[]) {
  if ((strncmp(argv[1], "server", 6) == 0) && (argc == 4)) {
    run_server(argv[2], argv[3], "out");
  } else if ((strncmp(argv[1], "client", 6) == 0) && (argc == 6)) {
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
  //initialize input files
  if ((infile = fopen(filename,"rb")) == NULL) {
    exit(2);
  }
  //connect to server
  if (socket_connect(&sock, host, port) != 0) {
    cipher_destroy(&cipher);
    fclose(infile);
    exit(2);
  }
  //read from file, encrypt and send to server
  while ((r = fread(buffer, 1, size, infile)) > 0) {
    cipher_encrypt(&cipher, buffer, encrypted, r);
    socket_send(&sock, r, encrypted);
  }
  //close file
  fclose(infile);
  //free resources
  cipher_destroy(&cipher);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}

void run_server(const char* port, const char* key, const char* filename) {
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
  memset(decrypted, 0, 50);
  //initialize output files
  if ((outfile = fopen(filename,"wb")) == NULL) {
    exit(2);
  }
  //bind socket and wait client
  if ((socket_bind_and_listen(&sock, port) != 0)
                || (socket_accept(&sock, &new_sock) != 0)) {
    cipher_destroy(&cipher);
    fclose(outfile);
    exit(2);
  }
  //receive encrypted stream, decrypt it and write it
  while ((s = socket_receive(&new_sock, size, buffer)) > 0) {
    cipher_decrypt(&cipher, buffer, decrypted, s);
    fwrite(decrypted, 1, s, outfile);
  }
  //close file
  fclose(outfile);
  //free resources
  cipher_destroy(&cipher);
  socket_shutdown(&new_sock);
  socket_destroy(&new_sock);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}
