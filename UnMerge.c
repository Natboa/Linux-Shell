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
	int f1,f2,f3,rbytes,wbytes;
	int f1_size;
	int cnt, num1, num2, arrsize;
	int cnt1 = 0, cnt2 = 0; //Counters for words of each file that was written already
	char str[BUFF_SIZE];
	char *arr[BUFF_SIZE];
	
	
	num1 = atoi(argv[4]);
	num2 = atoi(argv[5]);
	
	//Convert Num 1 and Num 2
	
	//OPENING FILE 1 TO READ FROM
	f1 = open(argv[1], O_RDONLY); //First txt file for reading
	if(f1 == -1){ //File opening error
		perror("open1");
		return 1;
	}
	//OPENING FILE 2 TO READ FROM
	f2 = open(argv[2], O_WRONLY|O_CREAT, 0644); //Third (new)txt file for writing
	//CHECK ACCESS FOR F2 && F3
	if(f2 == -1){ //File opening error
		perror("open3");
		exit(3);
	}
	
	f3 = open(argv[3], O_WRONLY|O_CREAT, 0644); //Third (new)txt file for writing
	if(f3 == -1){ //File opening error
		perror("open3");
		exit(3);
	}
	
	//Setting file sizes and resetting the pointers
	f1_size = lseek(f1,0,SEEK_END); 
	lseek(f1,0,0);
	//Reading the file into str
	if(read(f1, str, f1_size) != f1_size){
		perror("f1 reading error!\n");
		exit(4);
	}
	str[f1_size] = '\0';
	
	arrsize = arg_Div(str, arr); //Array of all the words of f1
	//For loop - for writing the words
	for (int i = 0; i < arrsize; i++) {
   	 // Write to file2
       		if (cnt1 < num1 && (cnt2 >= num2 || i % 2 == 0)) {
       			 wbytes = write(f2, arr[i], strlen(arr[i]));
       			 if (wbytes != strlen(arr[i])) {
       		         perror("write f2 error");
           	         exit(5);
       		 }
       		 write(f2, " ", 1); // Adds a  space after word
       		 cnt1++;
    		}
   	 //Write to the f3 file
   		 else if (cnt2 < num2) { // Use else if to ensure an exlusive write to f3 in fullfilment case
     	  	       wbytes = write(f3, arr[i], strlen(arr[i]));
       		       if (wbytes != strlen(arr[i])) {
           			  perror("write f3 error");
          	        	  exit(5);
       		       }
        		write(f3, " ", 1); // Add space after word
       			 cnt2++;
   		 }
       }
	
	printf("Mission Complete\n");
	close(f1);
	close(f2);
	close(f3);
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
