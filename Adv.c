#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>




int main(int argc, char* argv[]){
	pid_t pid;
	int f1;
	
	if(access("Commands/Advanced",F_OK) == -1){ //Check if folder exist
		if(mkdir("Commands/Advanced",0777) == -1){ //Handling error in file creation
			printf("Advanced file open error");
			return 1;
		}
	}
	
	//Creating txt file that contains the user commands	
	f1 = open("Commands/Advanced/Advanced_Commands",O_CREAT, 0644);
	if(f1 == -1){ //File didn't open correctly
		perror("open1");
		return 2;
	}
	
	pid = fork();
	
	if(pid == -1){ //Fork failure
		perror("Fork failure.\n");
		exit(-1);
	}	
	else if(pid == 0){//child process
		execlp("./Advanced_shell", "./Advanced_shell",argv[1], NULL);
		perror("Advanced Shell execution failure");
		exit(-1);
	}
			
	else //father process
		wait(NULL);
	
	close(f1);
	return 0;
} 
