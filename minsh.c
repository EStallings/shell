
/*+==========================================================================+*\

	required to use execvp
	execute command as separate process(fork followed by execvp)
	after execution of command terminates, print the following:
		"CompleteRun(PID:xxxx): commend-name -- user time xx.xx system time xx.xx"
	You can use "getrusage"(man -s 2 getrusage) to obtain child process clock values
	"&" = background job
	record pids for background jobs, check/terminate before shell exits
	"exit": minsh should check and terminate unfinished background jobs then terminate itself
	errors in executing commends should not terminate shell
	use "ps" and "kill" to find and clean processes

	not required to handle "<", ">", ">>", ";", "|", "&&"

\*+==========================================================================+*/

#define MAX_BUFFER 80
#define MAX_ARGS   10

#include <stdio.h>

int main(int argc,char **argv){
	char buffer[MAX_BUFFER];
	char *args[MAX_ARGS];
	int i,j;
	
	while(1){
		// get input
		printf("minsh-LB-ES: ");
		if(!fgets(buffer,MAX_BUFFER,stdin))return -1;

		// get args
		for(i=0;i<MAX_ARGS;++i) args[i] = NULL;
		for(i=0;i<MAX_BUFFER;++i)if(buffer[i]=='\n')buffer[i] = '\0';
		for(i=0,j=0;i<MAX_BUFFER;){
			while(buffer[i]==' ') buffer[i++] = '\0'; // XXX: this can run off the buffer
			args[j++] = buffer+i;
			while(buffer[i]!=' ' && i<MAX_BUFFER) ++i;
		}











		printf("ToRun: ");
		for(i=0;i<MAX_ARGS && args[i];++i)
			printf("%d:%s, ",i,args[i]);
		puts("");
/*
			ParseCommand buffer and set isBackground if '&' presents
			if(next command is "exit"){
				Handle unfinished background jobs, then terminate;
			}switch(fork()){
				case asChild:
					Display pre-command information
					use execvp to execute command
					break;
				case asParent:
					if(isBackground){
						Record information into background job list
					}else{
						Wait for child process to finish
						Display post-command information
					}break;
				case asError:
					break;
			}
		}
*/
	}
}
