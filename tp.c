#include <stdio.h>
#include <stdlib.h>

#include "cipher.h"
#include "socketTDA.h"

int write_hexa_file(FILE* pFile, unsigned char* buffer, size_t length) {
  return fwrite(buffer, 1, length, pFile);
}

int read_chunk(FILE *pFile, unsigned char* buf, int length) {
  //TODO: ver si fread lee de una cantidad length
  return fread(buf, 1, length, pFile);
}

void start_client(const char* port, const char* host) {
  int size = 5;
  char buffer[5] = "hola";
  socket_t sock;
  socket_create(&sock);
  socket_connect(&sock, host, port);
  socket_send(&sock, size, buffer);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}

void start_server(const char* port, const char* host) {
  int size = 5;
  char* buffer;
  socket_t sock, new_sock;
  socket_create(&sock);
  socket_bind_and_listen(&sock, port);
  socket_accept(&sock, &new_sock);
  socket_send(&sock, size, buffer);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}

int main(int argc, char const *argv[]) {
  start_server(argv[1], argv[2]);
  return 0;
}
