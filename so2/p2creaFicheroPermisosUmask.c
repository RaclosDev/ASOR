//Fijar la máscara de forma que los nuevos ficheros no tengan permiso de escritura para el grupo y ningún permiso para otros. 
// rwx-r-x----
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
umask(027);
   if(open("ej5",O_CREAT,0645) == -1)
       printf("Ha ocurrido un error.\n");
  
   return 1;
}

/*nacho@debian:~/Documentos/sockets$ ls -l
-rwxr-x--- 1 nacho nacho  0 dic 10 20:39 ej7.txt
nacho@debian:~/Documentos/sockets$ umask
0022
*/