//lsextendido.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){

   if(argc != 2 ){
       printf("p2.out: usage: p2.out [path]\n");
       return -1;
   }

   DIR *d = opendir(argv[1]);
   if(d == NULL ){
       perror("Error al abrir el directorio.\n");
       return -1;
   }

   struct dirent *it = readdir(d);
   struct stat buf;
   unsigned long int size = 0;
   char pathname[100], filename[100];
   while(it != NULL){
       char * name = it->d_name, *linkname;
       stat(strcpy(pathname, strcat(strcpy(pathname, argv[1]),strcat(strcpy(filename, "/"), name))),&buf);
       if(S_ISREG(buf.st_mode)){
           linkname = malloc(buf.st_size+1);
           if(readlink(pathname, linkname, 100) != -1){
               strcat(strcat(name, " -> "), linkname);
           } else {
               size += buf.st_blksize/8*buf.st_blocks;
           }

           if(access(pathname, X_OK)){
               strcat(name, "*");
           }
       }

       if(S_ISDIR(buf.st_mode)){
           strcat(name, "/");
       }

       printf("%s\n", name);
       it = readdir(d);
   } 
   printf("Total: %iKB\n", size/1024);

   return 1;
}
