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
	int f1, f2;
	int cnt1, cnt2;
	
	//check if files exist
	if((access(argv[1],F_OK) != 0) || (access(argv[2],F_OK) != 0) ){
		printf("one of the files doesnt exist!\n");
		exit(-1);
	}
	
	
	f1 = open(argv[1], O_RDONLY); //First txt file for reading
	if(f1 == -1){ //File opening error
		perror("open1");
		return 1;
	}
	f2 = open(argv[2], O_RDONLY); //Second txt file for reading
	if(f2 == -1){ //File opening error
		perror("open2");
		exit(2);
	}
	
	//getting length of files
	cnt1 = lseek(f1, 0, SEEK_END);
	cnt2 = lseek(f2, 0, SEEK_END);
	//comparing length of files
	if (cnt1 > cnt2) 
		printf("%s\n", argv[1]);
	else printf("%s\n", argv[2]);
	
	
	close(f1);
	close(f2);
	return 0;	

}
