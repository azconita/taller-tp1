#ifndef SOCKET_H
#define SOCKET_H

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct Socket {
  int sock;
} socket_t;

int socket_create(socket_t *s);
int socket_accept(socket_t *s, socket_t *new_s);
int socket_bind_and_listen(socket_t *s, unsigned short port);
int socket_connect(socket_t *s, const char* host_name, unsigned short port);

int socket_send(socket_t *s, size_t size, const char* buffer);
int socket_receive(socket_t *s, size_t size, const char* buffer);
int socket_destroy(socket_t *s);
void socket_shutdown(socket_t *s);

#endif
