//rw-r--r-x. 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

   if(open("ej5",O_CREAT,0645) == -1)
       printf("Ha ocurrido un error.\n");
  
   return 1;
}
/*
nacho@debian:~/Documentos/sockets$ ls -l
total 92
-rw-r--r-x 1 nacho nacho  0 dic 10 20:15 ej5
*/