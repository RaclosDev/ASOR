#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(){

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
	return 0;
}