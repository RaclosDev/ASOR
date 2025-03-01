#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv){

   sigset_t blockSet, blocked;
   sigemptyset(&blockSet);
   sigemptyset(&blocked);
   sigaddset(&blockSet, SIGTSTP);
   sigaddset(&blockSet, SIGINT);
   sigprocmask(SIG_BLOCK, &blockSet,NULL);

  // check if the number of arguments is correct
  if (argc != 2) {
    printf("ERROR: Introduce los segundos!\n");
    return -1;
  }

  // check if the argument passed is a number
  int secs;
  if(sscanf(argv[1], "%d", &secs) != 1){
    printf("ERROR: Introduce un numero como argumento\n");
    return -1;
  }

  //Obtenemos la variable de entorno
  char *sleep_secs = getenv("SLEEP_SECS");
  if(sleep_secs != NULL){
    secs = atoi(sleep_secs);
    printf("SLEEP_SECS tiene el valor: %d\n", secs);
  }else{
    printf("SLEEP_SECS no esta definida\n");
  }

  printf("Se va a dormir el proceso durante %d segundo(s)\n", secs);
  //Dormimos el proceso
  sleep(secs);

  if(sigpending(&blockSet) != -1){
   if(sigismember(&blockSet,SIGINT)){
       printf("Se recibió la señal SIGINT antes de desbloquear las señales.\n");
   }
   if(sigismember(&blockSet,SIGTSTP)){
       printf("Se recibió la señal SIGTSTP antes de desbloquear las señales.\n");
   }
  }
  sigprocmask(SIG_UNBLOCK, &blockSet,NULL);
  printf("Programa finalizado.\n");
  return 0;
}
