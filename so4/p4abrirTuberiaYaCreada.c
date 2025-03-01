#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>



int main(int argc, char **argv){

   if (argc < 2) {
     printf("ERROR: too few arguments.\n");
     return -1;
   }

   char *npipe = "tuberia";

   int fdp = open (npipe,O_WRONLY);
   write(fdp,argv[1], strlen(argv[1]));
   return 0;
}
