int main (int argc, char **argv) 
{ 
	pid_t child_pid; 
	char *cmdLine; 
	int maxc=80, len=80, readlen; 
	cmdLine = (char*) malloc(maxc*sizeof(char)); 
		// due to possible realloc, use malloc instead of leaving it in stack. 
	 
	while (1) 
	{ 
		if ((readlen = getline(&cmdline, &len, stdin)) > 0) 
		{ 
			ParseCommand cmdLine and set isBackground if “&” presents 
			if (next command is ’exit’) 
			{
				Handle unfinished background jobs, then terminate; 
			}
			switch (child_pid = fork()) 
			{ 
				case asChild: 
					Display pre-command information 
					use execvp to execute command 
					break;
				case asParent: 
					if (isBackground) 
					{ 
						Record information into background job list 
					} 
					Else 
					{ 
						Wait for child process to finish 
						Display post-command information 
					}
					break;
				case asError:
					break;
			} // end of switch 
		} // end of if 
	} // end of while 

	free(cmdLine);
} //end of main