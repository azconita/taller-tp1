#include "socketTDA.h"

int socket_create(socket_t *self, char *port) {
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sfd, s;
  struct sockaddr_storage peer_addr;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;       // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP

  s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(2);
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    self->sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (self->sock == -1)
      continue;
  }

  freeaddrinfo(result);           /* No longer needed */
}


int socket_bind_and_listen(socket_t *self, unsigned short port) {
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(struct sockaddr_in));

  // configure server information
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  serv_addr.sin_port = ntohs(port);

  // Decimos en que direccion local queremos escuchar, en especial el puerto
  // De otra manera el sistema operativo elegiria un puerto random
  // y el cliente no sabria como conectarse
  if (bind(self->sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
     printf("Error: %s\n", strerror(errno));
     close(self->sock);
     return 1;
  }


  // Cuanto clientes podemos mantener en espera antes de poder acceptarlos?
  if (listen(self->sock, 1) == -1) { //1 o 0?
     printf("Error: %s\n", strerror(errno));
     close(self->sock);
     return 1;
  }
}

int socket_connect(socket_t *self, const char* host_name, unsigned short port) {
  struct sockaddr_in serv_addr;
  // configure server information
  serv_addr.sin_family = AF_INET;
  inet_pton(AF_INET, host_name, &serv_addr.sin_addr.s_addr);
  //serv_addr.sin_addr.s_addr = htonl(host_name);
  serv_addr.sin_port = ntohs(port);
  if (connect(self->sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != -1) {
    close(self->sock);
  }
}

int socket_accept(socket_t *self, socket_t *new_s) {
  new_s->sock = accept(self->sock, NULL, NULL);   // aceptamos un cliente
  if (new_s->sock == -1) {
    printf("Error: %s\n", strerror(errno));
  }
}

int socket_destroy(socket_t *self) {
  close(self->sock);
}

int socket_send(socket_t *self, size_t size, const char *buffer) {
  int total_sent, sent;

  while((sent = send(self->sock, &buffer[total_sent], size - total_sent, MSG_NOSIGNAL)) >= 0) {
    total_sent += sent;
  }
  // if sent == 0: socket closed
  if (sent < 0) {
    printf("Error: %s\n", strerror(errno));
  }
}

int socket_receive(socket_t *self, size_t size, const char *buffer) {
  int total_received, received;

  while((received = recv(self->sock, (void*) &buffer[total_received], size - total_received, MSG_NOSIGNAL)) >= 0) {
    total_received += received;
  }
  // if sent == 0: socket closed
  if (received < 0) {
    printf("Error: %s\n", strerror(errno));
  }
}
