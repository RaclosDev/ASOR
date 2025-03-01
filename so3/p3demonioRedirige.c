#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv){

   if(argc < 2){
       printf("Usage: pro [command [options]]\n");
       return -1;
   }
   int pid = fork();
   if(pid == 0){
       if(chdir("/tmp") == -1){
           return -1;
       }
       setsid();
       int fd = open("./daemon.out",O_CREAT | O_RDWR, 00777);
       int fderr = open("./daemon.err", O_CREAT | O_RDWR, 00777);
       int null = open("/dev/null", O_CREAT | O_RDWR, 00777);
       int fd2 = dup2(fd,1);
       int fd3 = dup2(fderr, 2);
       int fd4 = dup2(null, 0);
       execvp(argv[1],argv + 1);
   }
   else if(pid > 0){
       // wait(0);
       printf("El comando terminó de ejecutarse.\n");
   }
   return 0;
}
