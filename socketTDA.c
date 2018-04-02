#include "socketTDA.h"

int socket_create(socket_t *self) {
  self->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (self->sock == -1)
      return 1;
  return 0;
}

int _get_hosts(struct addrinfo **result, const char* port, const char* host) {
  struct addrinfo hints;
  int s;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;       // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP

  s = getaddrinfo(host, port, &hints, result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    return 1;
  }
  return 0;
}

int socket_bind_and_listen(socket_t *self, const char* port) {
  struct addrinfo *results, *res;
  int s;
  bool not_bound = true;
  if (_get_hosts(&results, port, NULL) != 0)
    return 1;
  for (res = results; res != NULL && not_bound; res = res->ai_next) {
    s = bind(self->sock, res->ai_addr, res->ai_addrlen);
    if (s != 0) {
      printf("Error: %s\n", strerror(errno));
    } else {
      not_bound = false;
      break;
    }
  }
  freeaddrinfo(results);
  if (s != 0) {
    close(self->sock);
    return 1;
  }

  if (listen(self->sock, 1) == -1) { //1 o 0?
    printf("Error: %s\n", strerror(errno));
    close(self->sock);
    return 1;
  }
  return 0;
}

int socket_connect(socket_t *self, const char* host, const char* port) {
  struct addrinfo *results, *res;
  int s;
  if (_get_hosts(&results, port, host) != 0)
    return 1;
  for (res = results; res != NULL; res = res->ai_next) {
    if ((s = connect(self->sock, res->ai_addr, res->ai_addrlen)) == -1)
      printf("Error: %s\n", strerror(errno));
    else
      break;
  }
  freeaddrinfo(results);
  if (s == -1) {
    close(self->sock);
    return 1;
  }
  return 0;
}

int socket_accept(socket_t *self, socket_t *new_s) {
  struct sockaddr_un peer_addr;
  socklen_t peer_addr_size;
  peer_addr_size = sizeof(struct sockaddr_un);
  new_s->sock = accept(self->sock, (struct sockaddr *) &peer_addr,
                      &peer_addr_size);
  if (new_s->sock == -1) {
    printf("Error: %s\n", strerror(errno));
    return 1;
  }
  return 0;
}

int socket_destroy(socket_t *self) {
  close(self->sock);
  return 0;
}

void socket_shutdown(socket_t *self) {
   shutdown(self->sock, SHUT_RDWR);
}

int socket_send(socket_t *self, size_t size, const unsigned char *buffer) {
  int sent, total_sent = 0;

  while ((sent = send(self->sock, &buffer[total_sent], size - total_sent,
              MSG_NOSIGNAL)) > 0) {
    total_sent += sent;
  }
  // if sent == 0: socket closed
  if (sent < 0) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  return total_sent;
}

int socket_receive(socket_t *self, size_t size, const unsigned char *buffer) {
  int received, total_received = 0;

  while ((received = recv(self->sock, (void*) &buffer[total_received],
              size - total_received, MSG_NOSIGNAL)) > 0) {
    total_received += received;
  }
  // if received == 0: socket closed
  if (received < 0) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  return total_received;
}
