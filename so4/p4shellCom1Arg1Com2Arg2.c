#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv){
  if(argc < 4){
    printf("Usage: pipes command1 options1 | command2 options2.\n");
    return -1;
  }

  int fd[2];

  if(pipe(fd) == -1){
    printf("Error when creating pipe.\n");
    return -1;
  }
  int pid = fork();
  if(pid == 0){
    //hijo
    close(0);
    dup(fd[0]);
    close(fd[1]);
    close(fd[0]);
    if(execlp(argv[3],argv[3],argv[4],NULL) == -1){
      perror("Error when execute command");
      return -1;
    }
  }
  else if(pid != -1){
    //padre
    close(1);
    dup(fd[1]);
    close(fd[0]);
    close(fd[1]);
    if(execlp(argv[1],argv[1],argv[2],NULL) == -1){
      perror("Error when execute command");
      return -1;
    }
  }else{
    perror("Error when fork.");
    return -1;
  }
  return 0;
}