
/*+==========================================================================+*\

prompt: "minsh-LB: "
use "ps" and "kill" to find and clean processes

(50%)	whitespace separates commands, arguments, shell operators
	length of a command line to 80 characters
	number of arguments to a single command to 10
	required to use execvp

(20%)	Before command execution, print the following:
		"ToRun: command-name 1:arg1, 2:arg2, ... N:argN"
	execute command as separate process (fork followed by execvp)
	after execution of command terminates, print the following:
		"CompleteRun(PID:xxxx): commend-name -- user time xx.xx system time xx.xx"
	You can use "getrusage" (man -s 2 getrusage) to obtain child process clock values

(20%)	"&" = background job
	record pids for background jobs, check/terminate before shell exits

(10%)	"exit": minsh should check and terminate unfinished background jobs then terminate itself
	errors in executing commends should not terminate shell

	not required to handle "<", ">", ">>", ";", "|", "&&"

\*+==========================================================================+*/

int main(int argc,char **argv){
	pid_t child_pid;
	char *cmdLine;
	int maxc = 80,len = 80,readlen;
	cmdLine = (char*)malloc(maxc*sizeof(char));
	
	while (1){
		if ((readlen = getline(&cmdline,&len,stdin)) > 0){
			ParseCommand cmdLine and set isBackground if '&' presents
			if (next command is "exit"){
				Handle unfinished background jobs, then terminate;
			}switch (child_pid = fork()){
				case asChild:
					Display pre-command information
					use execvp to execute command
					break;
				case asParent:
					if (isBackground){
						Record information into background job list
					}else{
						Wait for child process to finish
						Display post-command information
					}break;
				case asError:
					break;
			}
		}
	}

	free(cmdLine);
}
