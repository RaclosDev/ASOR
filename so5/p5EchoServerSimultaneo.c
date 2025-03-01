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

int main(int argc, char **argv){

   if(argc < 3){
       printf("USAGE: sock <addr> <port>");
       return -1;
   }

   struct addrinfo hints;
   struct addrinfo *res;

   memset(&hints,0,sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   if(getaddrinfo(argv[1], argv[2], &hints, &res) != 0){
       printf("ERROR at getAddrInfo\n");
       return -1;
   }

   int sock = socket(res->ai_family, SOCK_STREAM, 0);

   if(bind(sock, res->ai_addr, res->ai_addrlen) != 0){
       printf("ERROR at binding.\n");
       return -1;
   }

   if(listen(sock, 5) != 0){
       printf("Error at listen.\n");
       return -1;
   }
   freeaddrinfo(res);

   char buf[2];
   char host[NI_MAXHOST];
   char serv[NI_MAXSERV];

   struct sockaddr_storage client_addr;
   socklen_t client_addrlen = sizeof(client_addr);


   while(1){
       int client = accept(sock, (struct sockaddr *) &client_addr, &client_addrlen);
       int pid = fork();
       if(pid == 0){
           getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
           printf("Conexion stablished with: %s|%s\n", host, serv);
           ssize_t max;
           while (max = recv(client, buf, 80, 0)) {
               buf[max] = '\0';
               if(strcmp(buf,"Q") == 0){
                   printf("Closing connection...\n");
                   close(client);
                   break;
               }
               printf("\tMensaje: %s\n", buf);
               send(client, buf, max, 0);
           }
       }else{
           close(client);
       }
             
   }

   return 0;
}
