#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define BUFF_SIZE 200

int arg_Div(char* str, char* arg_arr[]);

int main(int argc, char* argv[]){ 
	char str[BUFF_SIZE] = "",str1[BUFF_SIZE] = "";
	char *arg_arr[5];
	char strcnt[5]; //Buffers to hold string versions num1 num2
	int hcnt = atoi(argv[1]) , status;
	int cnt, f1,f2 ,wbytes, flag = 0;
	pid_t pid;
	
	
	f1 = open("Commands/Security/Security_Commands",O_WRONLY,0644); //Opening the command file
	if(f1 == -1){ //File didn't open correctly
		perror("open1");
		return 1;
	}
	
	while(1){ //main while loop for resuming the main function
		printf("SecShell>");
		flag = 0;
		memset(str,0,BUFF_SIZE); //Clear the buffer
		fgets(str, BUFF_SIZE, stdin);
		//copying the input to str1
		if(str[strlen(str)-1] == '\n')
			str[strlen(str)-1] = '\0';
		strcpy(str1,str);
		cnt = arg_Div(str, arg_arr);
		
		//COMMAND NUM 1 - Enc
		if(strcmp(arg_arr[0],"Enc")==0){
			if(cnt != 3){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
				perror("Fork failure.\n");
				exit(-1);
			}
			else if(pid == 0){//child process	
				execlp("./Enc", "./Enc", arg_arr[1],arg_arr[2],arg_arr[3] ,NULL); //CH N1
				perror("Enc execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
					
			}
		}
		
		//COMMAND NUM 2 - AdvEnc
		else if(strcmp(arg_arr[0],"AdvEnc")==0){
			if(cnt != 3){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
				perror("Fork failure.\n");
				exit(-1);
			}
			else if(pid == 0){//child process	
				execlp("./AdvEnc", "./AdvEnc", arg_arr[1],arg_arr[2],arg_arr[3] ,NULL); //CH N1
				perror("AdvEnc execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
					
			}
		}
		
		//COMMAND NUM 3 - Dec
		else if(strcmp(arg_arr[0],"Dec")==0){
			if(cnt != 3){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
				perror("Fork failure.\n");
				exit(-1);
			}
			else if(pid == 0){//child process	
				execlp("./Dec", "./Dec", arg_arr[1],arg_arr[2],arg_arr[3] ,NULL); //CH N1
				perror("Dec execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
					
			}
		}
		
		//COMMAND NUM 4 - AdvDec
		else if(strcmp(arg_arr[0],"AdvDec")==0){
			if(cnt != 3){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
				perror("Fork failure.\n");
				exit(-1);
			}
			else if(pid == 0){//child process	
				execlp("./AdvDec", "./AdvDec", arg_arr[1],arg_arr[2],arg_arr[3] ,NULL); //CH N1
				perror("Dec execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
					
			}
		}
		
		//COMMAND NUM 5 - History
		else if(strcmp(arg_arr[0],"History")==0){
			if(cnt != 1){ //Not enough parameters received
				printf("too many arguments\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			
			else if(pid == 0){//child process
				sprintf(strcnt, "%d", hcnt);
	                 	execlp("./History", "./History",strcnt,"Commands/Security/Security_Commands", NULL);
 				perror("History execution failure");
				exit(-1);
			}
			else{ //father process
				wait(NULL);
				hcnt++;
			}
		}
		
		
		//COMMAND NUM 6 - Esc				
		else if(strcmp(arg_arr[0],"Esc")==0){ //Command exit Entered
			if(cnt != 1){ //Can't receive parameters
				printf("Too many parameters!\n");
				continue;
			}
			//Sending the CNT of commands list
			f2 = open("temp2",O_WRONLY | O_CREAT,0644); //Txt file for the commands word counter
			//CHECK F2 OPENOING
			sprintf(strcnt, "%d", hcnt);
			wbytes= write(f2, strcnt, 1);
			if(wbytes != 1){
				perror("tempwrite1\n");
				exit(6);
			}
			close(f1);
			close(f2);
			return 0;	
		}
		
		else //Invalid command!
			printf("Not Supported!\n");
		if (flag == 1)	{
			sprintf(strcnt, "%d", hcnt);
			wbytes = write(f1,strcnt,1);
			wbytes = write(f1,". ",2);
			wbytes = write(f1,str1,strlen(str1)); //Write the latest command into Advanced_Commands
			wbytes = write(f1,"\n",1);
			hcnt++;
		}
		
	}//While end bracket
	close(f1);
	close(f2);
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
