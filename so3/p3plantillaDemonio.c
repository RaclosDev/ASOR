#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(){

   int pid = fork();
   if(pid == 0){
       if(chdir("/tmp") == -1){
           return -1;
       }
       setsid();
       printf("PID:  %i\nPPID: %i\nPGID: %i\nSID:  %i\n",
       getpid(),
       getppid(),
       getpgid(getpid()),
       getsid(getpid()));
       char *directory = malloc(sizeof(char)*(4096 + 1));
       struct rlimit limite;
      
       if (getrlimit(RLIMIT_NOFILE, &limite) == -1) {
           perror("No se ha podido acceder al limite de ficheros.");
           return -1;
       }
      
       getcwd(directory,4096);
       printf("Máximo de ficheros: %i\nDirectorio actual:  %s\n", limite.rlim_max, directory);
       }
   else if(pid > 0){
           //sleep(3);
           //printf("////////////////////////\nPID:  %i\nPPID: %i\nPGID: %i\nSID:  %i\n/////////////////////////\n",
           //getpid(),
           //getppid(),
           //getpgid(getpid()),
           //getsid(getpid()));
   }
   return 0;
}


//Si el padre finaliza primero, el PPID del hijo será 1. Si es al contrario y el hijo termina primero, entonces el PPID del hijo será el mismo que el PID del padre.
