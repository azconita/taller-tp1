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
  char buffer[5]= "hola";
  socket_t sock;
  socket_create(&sock);
  socket_connect(&sock, host, port);
  socket_send(&sock, size, buffer);
  socket_shutdown(&sock);
  socket_destroy(&sock);
}

void start_server(const char* port) {
  int size = 5;
  char buffer[5];
  socket_t sock, new_sock;
  socket_create(&sock);
  socket_bind_and_listen(&sock, port);
  socket_accept(&sock, &new_sock);
  socket_receive(&new_sock, size, buffer);
  socket_shutdown(&new_sock);
  socket_destroy(&new_sock);
  socket_shutdown(&sock);
  socket_destroy(&sock);
  printf("%s\n", buffer);
}

int main(int argc, char const *argv[]) {
  if(strcmp(argv[1],"server")==0)
    start_server(argv[2]);
  if(strcmp(argv[1], "client")==0)
    start_client(argv[2], argv[3]);
  return 0;
}
