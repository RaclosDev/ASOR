#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char** argv){

   if(argc != 2 ){
       printf("p2.out: usage: p2.out [path]\n");
       return -1;
   }
   int maj, min;
   struct stat buffer;
   if(stat(argv[1], &buffer) == -1)
       printf("Ha ocurrido un error al consultar el i-nodo.\n");
   else{
       printf("INFORMACION\n");
       maj = major(buffer.st_dev);
       printf("Major:      %i\n", maj);
       min = minor(buffer.st_dev);
       printf("Minor:      %i\n", min);
       printf("I-nodo:     %i\n", buffer.st_ino);

       if(S_ISLNK(buffer.st_mode))
           printf("Tipo:       Enlace\n");
       else if(S_ISREG(buffer.st_mode))
           printf("Tipo:       Fichero\n");
       else if(S_ISDIR(buffer.st_mode))
           printf("Tipo:       Directorio\n");
       else
           printf("Tipo:       Otro\n");

       time_t t = buffer.st_atime;
       struct tm *tu= localtime(&t);

       printf("Ultimo acc: %d:%d\n", tu->tm_hour, tu->tm_min);
   }

   return 1;
}
