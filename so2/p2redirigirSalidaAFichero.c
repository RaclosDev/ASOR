#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){

   if(argc != 2 ){
       printf("p2.out: usage: p2.out [path]\n");
       return -1;
   }

   int fd_new = open(argv[1], O_CREAT|O_RDWR);

   dup2(fd_new, STDOUT_FILENO);

   printf("Esta es la primera línea.\nEsta es la segunda.\n");

   return 1;
}

/* MISMO CON ERR TAMBIEN*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){

   if(argc != 2 ){
       printf("p2.out: usage: p2.out [path]\n");
       return -1;
   }

   int fd_new = open(argv[1], O_CREAT|O_RDWR);

   dup2(fd_new,STDERR_FILENO);

   dup2(fd_new, STDOUT_FILENO);

   printf("Esta es la primera línea.\nEsta es la segunda.\n");

   return 1;
}
