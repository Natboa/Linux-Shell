#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	int f1;
	
	
	//check if files exist
	if((access(argv[1],F_OK) != 0)){
		printf("file doesnt exist!\n");
		exit(0);
	}
	remove(argv[1]);
	return 0;
}
