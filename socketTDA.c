#include "socketTDA.h"

int socket_create(socket_t *s);
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sfd, s;
  struct sockaddr_storage peer_addr;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;       // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP

  s = getaddrinfo(NULL, argv[1], &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(2);
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;
  }

  freeaddrinfo(result);           /* No longer needed */
  s->sfd;
}


int socket_bind_and_listen(socket_t *self, unsigned short port) {
  // Decimos en que direccion local queremos escuchar, en especial el puerto
  // De otra manera el sistema operativo elegiria un puerto random
  // y el cliente no sabria como conectarse
  s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
  if (s == -1) {
     printf("Error: %s\n", strerror(errno));
     close(skt);
     freeaddrinfo(ptr);
     return 1;
  }

  freeaddrinfo(ptr);

  // Cuanto clientes podemos mantener en espera antes de poder acceptarlos?
  s = listen(skt, 20);
  if (s == -1) {
     printf("Error: %s\n", strerror(errno));
     close(skt);
     return 1;
  }
}

int socket_connect(socket_t *s, const char* host_name, unsigned short port) {
  if (connect(s->sock, rp->ai_addr, rp->ai_addrlen) != -1)
    close(s->sock);
  }
}

int socket_accept(socket_t *s, socket_t *new_s);
  new_s->sock = accept(skt, NULL, NULL);   // aceptamos un cliente
  if (new_s->sock == -1) {
    printf("Error: %s\n", strerror(errno));
}

int socket_destroy(socket_t *s) {
  close(s->sock)
}
