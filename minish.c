
/*+==========================================================================+*\

	minish.c
	For CS481, Fall 2014
	Prof. Wei Shu

	By Luke Balaoro and Ezra Stallings

\*+==========================================================================+*/

#include <sys/resource.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_BUFFER 128
#define MAX_ARGS   16

struct node{
	struct node *prev;
	pid_t pid;
}*currentNode=NULL;

int main(int argc,char **argv){
	char buffer[MAX_BUFFER];
	char *args[MAX_ARGS];
	unsigned int i,j,k,bkgnd;

	while(1){
		// get input
		printf("minsh-LB-ES: ");
		if(!fgets(buffer,MAX_BUFFER,stdin))return -1;

		// get args
		for(i=0;i<MAX_ARGS;++i)args[i]=NULL;
		for(i=j=bkgnd=0,k=1;i<MAX_BUFFER&&j<MAX_ARGS;++i)switch(buffer[i]){
			case '&':bkgnd=1;
			case ' ':case '\n':k=1;buffer[i]='\0';break;
			default:if(k)args[j++]=buffer+i;k=0;break;
			case '\0':i=MAX_BUFFER;break;
		}

		// print ToRun
		printf("ToRun: ");
		for(i=0;i<MAX_ARGS && args[i];++i)printf("%d:%s, ",i,args[i]);
		puts("");

		// parse args, cleanup before exiting
		if(!j)continue;
		if(!strncmp(args[0],"exit",4))while(1){
			if(currentNode){
				struct node *del=currentNode;
				kill(currentNode->pid,SIGKILL);
				currentNode=currentNode->prev;
				free(del);
			}else return 0;
		}

		// run command
		pid_t p,pid;
		switch(pid=fork()){
			case 0:execvp(args[0],args);
			case -1:return -1;
			default:if(!bkgnd){
				struct rusage begin,end;
				getrusage(RUSAGE_CHILDREN,&begin);
				waitpid(pid,NULL,0);
				getrusage(RUSAGE_CHILDREN,&end);
				printf("CompleteRun(PID:%d): %s -- user time %ld.%06ld system time %ld.%06ld\n",pid,args[0],
				       end.ru_utime.tv_sec-begin.ru_utime.tv_sec,end.ru_utime.tv_usec-begin.ru_utime.tv_usec,
				       end.ru_stime.tv_sec-begin.ru_stime.tv_sec,end.ru_stime.tv_usec-begin.ru_stime.tv_usec);
			}else{
				struct node *n=malloc(sizeof(struct node));
				n->prev=currentNode;
				n->pid=pid;
				currentNode=n;
			}break;
		}
	}
}
