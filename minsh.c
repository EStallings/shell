
/*+==========================================================================+*\

prompt: "minsh-LB: "
use "ps" and "kill" to find and clean processes

(50%)	The program waits for the user to type a command, then parse and execute the command.
	Then, your minsh should wait for the command to finish if it is not a background job.
	whitespace separates commands, arguments, shell operators.
	length of a command line to 80 characters.
	number of arguments to a single command to 10.
	The command can be the name of an executable file in any directory specified by the PATH environment variable.
	You are required to use execvp to execute user commends (using anything else, such as system, leads to no credit).
	The command may be followed by options that are valid for that command.
	For example, if the command string is "ls -l", your program will execute the file "/bin/ls" with the option string "-l".

(20%)	Command information display:
	Before attempting to start commends execution, your program will be required to print a command-information line for checking and verifying purpose.
	The format should be "ToRun: command-name 1:arg1, 2:arg2, ... N:argN".
	Then your program will execute the command as a separate process (fork followed by execvp).
	Wait until the execution of the command terminates, print another line as "CompleteRun(PID:xxxx): commend-name -- user time xx.xx system time xx.xx".
	You can choose to use "getrusage" (man -s 2 getrusage) to obtain your child process' clock values.
	You are not required to handle I/O redirections, such as "<", ">", ">>" (leaving them to a later assignment).

(20%)	You are required to deal with a background job with an ampersand "&" at the end.
	Your shell should execute the program and immediately return to the shell prompt.
	Meanwhile, your shell should keep records for those spawn process IDs and check/terminate them before your shell exists.
	You are not required to handle shell command operators, such as ";", "|", "&&", etc (leaving them to a later assignment).

(10%)	Clean exiting and error handling
	If a user types "exit", your minsh should check and terminate any unfinished background jobs then terminate itself.
	Should you encounter any errors in executing commends, your shell must not terminate.

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
