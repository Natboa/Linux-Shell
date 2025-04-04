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
	int f1,f2,f3,f4, rbytes, wbytes, wbytes_temp; //File descriptors 
	int f1_size, f2_size;
	int cnt1 = 0, cnt2 = 0, max_cnt, i; //flag for Merge Command successs
	char str1[BUFF_SIZE], str2[BUFF_SIZE];
	char *arr1[BUFF_SIZE], *arr2[BUFF_SIZE];
	char temp[5];
	
	
	
	f1 = open(argv[1], O_RDONLY); //First txt file for reading
	if(f1 == -1){ //File opening error
		perror("File opening error 1");
		return 1;
	}
	
	f2 = open(argv[2], O_RDONLY); //Second txt file for reading
	if(f2 == -1){ //File opening error
		perror("File opening error 2");
		exit(2);
	}
	
	
	f3 = open(argv[3], O_WRONLY|O_CREAT, 0644); //Third (new)txt file for writing
	if(f3 == -1){ //File opening error
		perror("File opening error 3");
		exit(3);
	}
	
	
	f4 = open("temp", O_WRONLY|O_RDONLY|O_CREAT, 0644); //Temp file for the size of each files
	if(f4 == -1){ //File opening error
		perror("File opening error 4");
		exit(4); 
	}
	//Setting file sizes and resetting the pointers
	f1_size = lseek(f1,0,SEEK_END); 
	lseek(f1,0,0); 
	f2_size = lseek(f2,0,SEEK_END); 
	lseek(f2,0,0);
	
	//Reading the files into str1, str2
	if(read(f1, str1, f1_size) != f1_size){
		perror("f1 reading error!\n");
		exit(5);
	}
	str1[f1_size] = '\0';
	
	if(read(f2, str2, f2_size) != f2_size){
		perror("f2 reading error!\n");
		exit(5);
	}
	str2[f2_size] = '\0';
	
	
	cnt1 = arg_Div(str1, arr1); //arr1 of words of f1
	cnt2 = arg_Div(str2, arr2); //arr2 of words of f2
	
	sprintf(temp, "%d%d", cnt1, cnt2);
	
	wbytes_temp= write(f4, temp, 2);
	if(wbytes_temp != 2){
		perror("tempwrite1\n");
		exit(6); 
	}
	
	//Max amount of words check
	if(cnt1 >= cnt2)
		max_cnt = cnt1;
	else
		max_cnt = cnt2;
	
	
	arr1[cnt1-1][strlen(arr1[cnt1-1])-1] = NULL;
	arr2[cnt2-1][strlen(arr2[cnt2-1])-1] = NULL;
	
	
	for(i = 0; i < max_cnt; i++){
		if(cnt1 > 0) { //There are still words from f1 
			wbytes = write(f3, arr1[i], strlen(arr1[i]));
			if(wbytes != strlen(arr1[i])){
				perror("write1\n");
				exit(6);
			}
			if(!(cnt1 == 1 && cnt2 == 0)) 
				write(f3, " ", 1);
			
			cnt1--;
		}
		
		if(cnt2 > 0) { //There are still words from f1 
			wbytes = write(f3, arr2[i], strlen(arr2[i]));
			if(wbytes != strlen(arr2[i])){
				perror("write2\n");
				exit(7);
			}
			if(!(cnt2 == 1 && cnt1 == 0)) 
				write(f3, " ", 1);
				
			cnt2--;
		}
	}
	
	

	printf("Mission Complete\n");
	
	close(f1);
	close(f2);
	close(f3);
	close(f4);
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
