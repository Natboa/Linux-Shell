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
	int f1, file_size, wbytes, i;
	char str[BUFF_SIZE];
	char ch = argv[2][0], path[BUFF_SIZE];
	
	strcpy(path,"Encryption_File/");
	
	//check if file exist or already encrypted
	if(access(argv[1],F_OK) != 0) {
		printf("Encryption option not Supported\n");
		return 1;
	}
	f1 = open(argv[1], O_RDONLY); //First txt file for reading
	if(f1 == -1){ //File opening error
		perror("open1");
		return 1;
	}
	//getting length of file
	file_size = lseek(f1,0,SEEK_END); 
	lseek(f1,0,0); 
	
	//reading from the file
	if(read(f1, str, file_size) != file_size){
		perror("f1 reading error!\n");
		exit(2);
	}
	
	//encrypting the string
	for (i = 0; i < strlen(str); i++) {
		str[i] = str[i] ^ ch;
	}
	
	close(f1);
	
	//deleting the file
	if (remove(argv[1]) != 0) {
		perror("delete error");
		exit(3);	
	}
	
	//creating the path with the name of the file
	strcat(path,argv[1]);
	
	//creating the file in a diffrent place
	f1 = open(path, O_WRONLY | O_CREAT, 0644);
	if(f1 == -1){ //File opening error
		perror("open1");
		exit(4);
	}
	
	//writing the encrypted messege to the file
	wbytes = write(f1, str, file_size);
	if(wbytes != file_size){
		perror("tempwrite1\n");
		exit(5); 
	}

	close(f1);
	printf("Mission Complete\n");
	return 0;
	
}
