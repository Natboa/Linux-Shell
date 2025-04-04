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
	int f1, wbytes,file_size;
	char str[BUFF_SIZE], *path = argv[2], hnum[BUFF_SIZE];
	
	
	//check if files exist
	if(access(path,F_OK) != 0){
		printf("no commands entered yet!\n");
		exit(0);
	}
	
	//printf("%s",argv[1]);
	f1 = open(path, O_RDWR | O_APPEND, 0644); //First txt file for reading
	if(f1 == -1){ //File opening error
		perror("open1");
		return 1;
	}
	//Treating the History name 
	strcpy(hnum,argv[1]);
	strcat(hnum,". History\n");
	//Writing the history name
	wbytes= write(f1, hnum, strlen(hnum));
	if(wbytes!= strlen(hnum)){
		perror("history write1\n");
		exit(2); 
	}
	
	
	file_size = lseek(f1,0,SEEK_END);
	lseek(f1,0,0);
	if(read(f1, str, file_size) != file_size){
		perror("f1 reading error!\n");
		exit(3);
	}
	printf("%s",str);
	close(f1);
	return 0;
}
