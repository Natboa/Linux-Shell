#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define BUFF_SIZE 200


int arg_Div(char* str, char* arg_arr[]);// Declaration of function that sort the users input into 2 catagotries - command and inputs(max 3 input)



int main(int argc, char* argv[]){
	pid_t pid;
	char str[BUFF_SIZE] = "";
	char *arg_arr[5], strtemp[5], strcnt[5] = "1", strcnt2[5] = "1";
	int f1,f2, cnt, fsize;
	
	
	
	if( mkdir("Commands",0777) == -1){ //Handling error in file creation
		printf("Commands file open error");
		return 1;
	}
	if( mkdir("Encryption_File",0777) == -1){ //Handling error in file creation
		printf("Encryption_File open error");
		return 2;
	}
	if( mkdir("Encryption_File/Adv_Enc",0777) == -1){
		printf("Adv_Enc open error");
		return 3;
	}
	

	
	
	while(1){ //main while loop for resuming the main function
		printf("StandShell>");
		memset(str,0,BUFF_SIZE); //Clear the buffer
		fgets(str, sizeof(str), stdin);
		if(str[strlen(str)-1] == '\n')
			str[strlen(str)-1] = '\0';
			
		cnt = arg_Div(str, arg_arr);
		if(cnt>4){ //Wrong amount of arguments
			printf("Too many arguments!!");
			continue;
		}
		
		//COMMAND NUM 1 - Adv
		if(strcmp(arg_arr[0],"Adv")==0){ //Command Adv Entered
			if(cnt != 1){ //Can't receive parameters
				printf("Too many parameters!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
				execlp("./Adv", "./Adv", strcnt, NULL);
				perror("Adv execution failure");
				exit(-1);
			}
			else{ //father process
				wait(NULL);
			}
			
			//Treating the CNT of each command written sentence
			if(access("temp1",F_OK) == 0){
				f1 = open("temp1",O_RDONLY,0644);
				
				if(f1 == -1){ //File opening error
					perror("opentemp1");
					exit(-1);
				}
				fsize = lseek(f1,0,SEEK_END); 
				lseek(f1,0,0); 
				if(read(f1,strtemp,fsize) != fsize){
					perror("temp1 reading error!\n");
					exit(-1);
				}
				//Copying strtemp into strcnt
				strcpy(strcnt,strtemp); //strcnt = %d(curr num of commands %d.)
				close(f1);
				remove("temp1"); //Deleting the temp
			}
		}
		//COMMAND NUM 2 - Security
		else if(strcmp(arg_arr[0],"Security")==0){ //Command Adv Entered
			if(cnt != 1){ //Can't receive parameters
				printf("Too many parameters!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
				execlp("./Security", "./Security",strcnt2, NULL);
				perror("Security execution failure");
				exit(-1);
			}
			else{ //father process
				wait(NULL);
			}
			
			//Treating the CNT of each command written sentence in SEC
			if(access("temp2",F_OK) == 0){
				f2 = open("temp2",O_RDONLY,0644);
				if(f2 == -1){ //File opening error
				perror("File opening error 1");
				return 1;
				}
				
				if(f1 == -1){ //File opening error
					perror("opentemp2");
					exit(-1);
				}
				fsize = lseek(f2,0,SEEK_END); 
				lseek(f2,0,0); 
				if(read(f2,strtemp,fsize) != fsize){
					perror("temp2 reading error!\n");
					exit(-1);
				}
				//Copying strtemp into strcnt
				strcpy(strcnt2,strtemp); //strcnt = %d(curr num of commands %d.)
				close(f2);
				remove("temp2"); //Deleting the temp
			}
		}
		
		//COMMAND NUM 3 - exit
		else if(strcmp(arg_arr[0],"exit")==0){ //Command exit Entered
			if(cnt != 1){ //Can't receive parameters
				printf("Too many parameters!\n");
				continue;
			}

			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
				execlp("./exit", "./exit", NULL);
				perror("exit execution failure");
				exit(-1);
			}
			else{ //father process
				wait(NULL);
				break;
			}
		}
		
		
		//Standard linux commands
		else{ 
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
				execvp(arg_arr[0],arg_arr);
				printf("Not supported!\n"); //In case of unsupported command
				exit(-1);
			}
			else{ //father process
				wait(NULL);
			}
		}
	
	}
	return 0; 
}

int arg_Div(char* str,char* arg_arr[]){
	int cnt = 0;
	char *word;
	char *strtmp;
	
	word = strtok(str, " ");
	arg_arr[cnt] = word;
	cnt++;
	while (1) {
		word = strtok(NULL, " ");
		if(!word)
			break; //No more user inputs
		arg_arr[cnt] = word;
		cnt++;
	}
	arg_arr[cnt] = NULL;
	return cnt;
}

