/* want to explore exec followed by arbitrary code 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void){
	int counter = 0;
	pid_t ret;
	if((ret = fork()) < 0){
		fprintf(stderr, "fork error\n");
		exit(EXIT_FAILURE);
	}else if(ret == 0){
		printf("%d", ++counter);
		//execlp("ls", "ls", NULL);
	}else{
		wait(NULL);
		printf("%d", counter);
	}
	printf("Process %d exiting...\n", getpid());
	exit(EXIT_SUCCESS);
}
