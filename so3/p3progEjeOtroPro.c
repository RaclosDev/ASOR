#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char **argv){

   if(argc < 3 || argc > 4){
       printf("Usage: pro system|execvp command [cmd-options]\n");
       return -1;
   }
   if(strcmp(argv[1], "system") == 0){
       char *cmd = malloc(sizeof(char)*4096);
       strcpy(cmd, argv[2]);
       if(argc == 4)
           strcat(cmd," ");
           strcat(cmd,argv[3]);
       system(cmd);
   } else if(strcmp(argv[1], "execvp") == 0){
       execvp(argv[2],argv + 2);
   }
   else{
       printf("Error: unexpected version param.\n");
       return -1;
   }
   printf("El comando terminó de ejecutarse.\n");
   return 0;
}

//Solamente se imprime la cadena cuando se usa la versión de system. Esto sucede porque execvp sustituye la imagen del proceso, haciendo que a partir de esa línea no se ejecuten más instrucciones del programa.
