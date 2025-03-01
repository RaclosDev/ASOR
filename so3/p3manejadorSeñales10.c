#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <signal.h>

volatile int num_int = 0;
volatile int num_tstp = 0;

void action(int signal){
   switch (signal)
   {
   case SIGINT:
       num_int++;
       break;
   case SIGTSTP:
       num_tstp++;
       break;
   }
}

int main(int argc, char **argv){

   struct sigaction act;
   sigaction(SIGINT, NULL, &act);
   act.sa_handler = action;
   sigaction(SIGINT, &act, NULL);
   sigaction(SIGTSTP, NULL, &act);
   act.sa_handler = action;
   sigaction(SIGTSTP, &act, NULL);

   sigset_t set;
   sigemptyset(&set);

   while(num_tstp + num_int < 10){
       sigsuspend(&set);
   }

   printf("Se han capturado las señales:\nSIGINT:  %i\nSIGTSTP: %i\n", num_int, num_tstp);
   return 0;
}
