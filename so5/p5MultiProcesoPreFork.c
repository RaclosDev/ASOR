#include <sys/types.h>

#include <sys/socket.h>

#include <stdio.h>

#include <errno.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <netdb.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <sys/select.h>

#include <unistd.h>

int main(int argc, char ** argv) {

  if (argc < 3) {
    printf("USAGE: sock <addr> <port>\n");
    return -1;
  }

  struct addrinfo hints;
  struct addrinfo * res;

  memset( & hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  int getaddrinfo_ret = getaddrinfo(argv[1], argv[2], & hints, & res);
  if (getaddrinfo_ret != 0) {
    printf("ERROR at getAddrInfo: %s\n", gai_strerror(getaddrinfo_ret));
    return -1;
  }

  int sock = socket(res -> ai_family, SOCK_DGRAM, 0);
  if (sock == -1) {
    printf("ERROR at creating socket: %s\n", strerror(errno));
    return -1;
  }

  if (bind(sock, res -> ai_addr, res -> ai_addrlen) != 0) {
    printf("ERROR at binding: %s\n", strerror(errno));
    return -1;
  }
  freeaddrinfo(res);

  int pid = fork();

  char buf[3];
  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];

  struct sockaddr_storage client_addr;
  socklen_t client_addrlen = sizeof(client_addr);

  fd_set set;
  int fd = -1;
  int mode = -1;

  while (1) {
    while (fd == -1) {
      FD_ZERO( & set);
      FD_SET(0, & set);
      FD_SET(sock, & set);
      fd = select(sock + 1, & set, NULL, NULL, NULL);
    }

    if (FD_ISSET(0, & set)) {
      read(0, buf, 2);
      buf[1] = '\0';
      if (strcmp(buf, "q") == 0) {
        printf("Exiting...\n");
        return 0;
      }
    } else if (FD_ISSET(sock, & set)) {
      recvfrom(sock, buf, 2, 0, (struct sockaddr * ) & client_addr, & client_addrlen);
      buf[1] = '\0';
      getnameinfo((struct sockaddr * ) & client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
      printf("MSG rcv from %s:%s: %s\n", host, serv, buf);
      if (buf[0] == 'q' || buf[0] == 'Q') {
        printf("Exiting...\n");
        return 0;
      }
      if (buf[0] == 't' || buf[0] == 'T') {
        size_t len = strftime(tbuff, max, "%I:%M:%S %p", tm);
        tbuff[len] = '\0';
        sendto(sock, tbuff, len, 0, (struct sockaddr * ) & client_addr, client_addrlen);
        printf("Time dispatched by: %i\n", pid);
        sleep(1);
      } else if (buf[0] == 'd' || buf[0] == 'D') {
        size_t len = strftime(tbuff, max, "%Y-%m-%d", tm);
        tbuff[len] = '\0';
        sendto(sock, tbuff, len, 0, (struct sockaddr * ) & client_addr, client_addrlen);
        printf("Date dispatched by: %i\n", pid);
        sleep(1);
      } else {
        printf("Command not supported by: %i\n", pid);
        sleep(1);
      }
    }
  }
  return 0;
}