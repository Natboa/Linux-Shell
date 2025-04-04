#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>



int main(int argc, char* argv[]){
	
	
	printf("Goodbye\n");
	//deleting the folder Commands:
	
	//Case ONE - Advanced_Commands file exist CHECK
	if(access("Commands/Advanced/Advanced_Commands",F_OK) == 0){
		if (remove("Commands/Advanced/Advanced_Commands") != 0) {
			perror("Advanced_Commands delete error");
			return 1;
		}
	}
	//Case TWO - Advanced folder exist CHECK
	if(access("Commands/Advanced",F_OK) == 0){
		if (remove("Commands/Advanced") != 0) {
			perror("Advanced folder delete error"); 				
			return 1;
		}
	}
	//CASE 3 - Security_commands file exist
	if(access("Commands/Security/Security_Commands",F_OK) == 0){
		if (remove("Commands/Security/Security_Commands") != 0) {
			perror("Security_Commands delete error"); 
			return 1;
		}
	}
	
	//CASE 4 - Security folder exist
	if(access("Commands/Security",F_OK) == 0){
		if (remove("Commands/Security") != 0) {
			perror("Security folder delete error");
			return 1;
		}
	}
	
	//Case X - Commands folder removal
	if (rmdir("Commands") != 0) {
		perror("Commands delete error");
		return 1;
	}
	return 0;
}
