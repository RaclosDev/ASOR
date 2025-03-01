#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(){


   int padre_h[2], hijo_p[2];

   pipe(padre_h);
   pipe(hijo_p);
   int pid = fork();
   if(pid == 0){
       //hijo
       close(hijo_p[0]);
       close(padre_h[1]);
       int  cont =  0;
       char *buff;
       while(cont < 10){
           buff =  malloc(sizeof(char)*40);
           ssize_t size = read(padre_h[0],buff,40);
           buff[size] = '\0';
           cont ++;
           printf("\nHijo: %s\n",buff);
           sleep(1);
           if(cont < 10)
               write(hijo_p[1],"1",1);
           else
               write(hijo_p[1],"q",1);
       }
       close(padre_h[0]);
       close(hijo_p[1]);
   }
   else if(pid != -1){
       //padre
       close(hijo_p[1]);
       close(padre_h[0]);
       char *buff, control = 'c';
       while(control != 'q'){
           buff =  malloc(sizeof(char)*40);
           ssize_t size = read(STDIN_FILENO,buff,40);
           buff[size] = '\0';
           write(padre_h[1], buff, 40);
           read(hijo_p[0],&control,1);
       }
       close(padre_h[1]);
       close(hijo_p[0]);
   }else{
       printf("Error when fork.\n");
       return -1;
   }
   return 0;
}
