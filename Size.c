#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define BUFF_SIZE 200 

int main(int argc, char* argv[]){
	int f1;
	
	
	//check if files exist
	if((access(argv[1],F_OK) != 0)){
		printf("file doesnt exist!\n");
		exit(-1);
	}
	
	f1 = open(argv[1], O_RDONLY); //First txt file for reading
	if(f1 == -1){ //File opening error
		perror("open1");
		return 1;
	}
	printf("Number of characters in file: %d\n", lseek(f1, 0, SEEK_END) - 1);
	close(f1);
	return 0;
}
