#ifndef SOCKET_H
#define SOCKET_H

//#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct Socket {
  int sock;
} socket_t;

int socket_create(socket_t *self);
int socket_accept(socket_t *self, socket_t *new_sock);
int socket_bind_and_listen(socket_t *self, const char* port);
int socket_connect(socket_t *self, const char* host, const char* port);

int socket_send(socket_t *self, size_t size, const char *buffer);
int socket_receive(socket_t *self, size_t size, const char *buffer);
int socket_destroy(socket_t *self);
void socket_shutdown(socket_t *self);

#endif
