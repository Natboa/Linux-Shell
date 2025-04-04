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
	char str[BUFF_SIZE] = "",str1[BUFF_SIZE] = "", strtemp[5];
	char *arg_arr[5];
	char num1_str[10],num2_str[10], strcnt[5]; //Buffers to hold string versions num1 num2
	int num,num1,num2;
	int cnt, f1,f2, ftemp, wbytes, flag = 0, hcnt = atoi(argv[1]);
	pid_t pid;
	int status;


	
	f1 = open("Commands/Advanced/Advanced_Commands", O_RDWR | O_APPEND ,0644); //Opening the command file
	if(f1 == -1){ //File didn't open correctly
		perror("open1");
		return 2;
	}
	
	
	while(1){ //main while loop for resuming the main function
		printf("AdvShell>");
		flag = 0;
		memset(str,0,BUFF_SIZE); //Clear the buffer
		fgets(str, BUFF_SIZE, stdin);
		if(str[strlen(str)-1] == '\n')
			str[strlen(str)-1] = '\0';
		//copying the input to str1
		strcpy(str1,str);
		cnt = arg_Div(str, arg_arr);
		
		//COMMAND NUM 1 - Merge
		if(strcmp(arg_arr[0],"Merge")==0){
			if(cnt != 4){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
				perror("Fork failure.\n");
				exit(-1);
			}
			else if(pid == 0){//child process
				execlp("./Merge", "./Merge", arg_arr[1],arg_arr[2],arg_arr[3] ,NULL); //CH N1
				perror("Merge execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
					
			}
			//Opening temp file to return counters of words 
			//Checking first if the temp file exist
			if(access("temp",F_OK) == 0){
				ftemp = open("temp",O_RDONLY,0644);
				if(ftemp == -1){ //File opening error
					perror("opentemp");
					exit(-1);
				}
				if(read(ftemp,strtemp,2) != 2){
					perror("ftemp reading error!\n");
					exit(-1);
				}
				num = atoi(strtemp);
				num1 = num/10; //Left digit -  count of File 1 
				num2 = num%10; //Right digit - count of File 2
				close(ftemp);
				remove("temp"); //Deleting the temp
			}
			
		}
		//COMMAND NUM 2 - UNMERGE
		else if(strcmp(arg_arr[0],"UnMerge")==0){
			if(cnt != 4){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
				
       			        sprintf(num1_str, "%d", num1); // Convert num1 to string
       			        sprintf(num2_str, "%d", num2); // Convert num2 to string
       			        
	                 	execlp("./UnMerge", "./UnMerge", arg_arr[1],arg_arr[2],arg_arr[3],num1_str,num2_str ,NULL); //CH N1
 				perror("UnMerge execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
			}
		}
		//COMMAND NUM 3 - FindMax
		else if(strcmp(arg_arr[0],"FindMax")==0){
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
				
	                 	execlp("./FindMax", "./FindMax", arg_arr[1],arg_arr[2], NULL);
 				perror("FindMax execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
			}
		}
		//COMMAND NUM 4 - Size
		else if(strcmp(arg_arr[0],"Size")==0){
			if(cnt != 2){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
	                 	execlp("./Size", "./Size", arg_arr[1], NULL);
 				perror("Size execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
			}
		}
		//COMMAND NUM 5 - Delete
		else if(strcmp(arg_arr[0],"Delete")==0){
			if(cnt != 2){ //Not enough parameters received
				printf("Missing parameters!!!!\n");
				continue;
			}
			pid = fork();
			if(pid == -1){ //Fork failure
			perror("Fork failure.\n");
			exit(-1);
			}
			else if(pid == 0){//child process
	                 	execlp("./Delete", "./Delete", arg_arr[1], NULL);
 				perror("Delete execution failure");
				exit(-1);
			}
			else{ //father process
				wait(&status);
				if(status == 0)
					flag = 1;
			}
		}
		
		//COMMAND NUM 6 - History
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
	                 	execlp("./History", "./History",strcnt,"Commands/Advanced/Advanced_Commands", NULL);
 				perror("History execution failure");
				exit(-1);
			}
			else{ //father process
				wait(NULL);
				hcnt++;
			}
		}
		
			
		//COMMAND NUM 7 - Esc				
		else if(strcmp(arg_arr[0],"Esc")==0){ //Command exit Entered
			if(cnt != 1){ //Can't receive parameters
				printf("Too many parameters!\n");
				continue;
			}
			//Sending the CNT of commands list
			f2 = open("temp1",O_WRONLY | O_CREAT,0644); //Txt file for the commands word counter
			if(f2 == -1){ //File opening error
				perror("File opening error 1");
				return 1;
			}	
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
		
	}
	
	
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

