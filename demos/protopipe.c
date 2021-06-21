/*	emulate the command:
 *		ls | grep c | grep r
 *	
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

	int a[] = {9,8,7,6};
	int ap = 1;
	int fd[2];
	pid_t pid;
	
	if(pipe(fd) < 0){
		fprintf(stderr, "pipe error\n");
		exit(EXIT_FAILURE);
	}

	if((pid = fork()) < 0){
		fprintf(stderr, "fork error\n");
		exit(EXIT_FAILURE);
	}
	else if(pid > 0){
//		close(fd[0]);

		printf("%d\n", a[ap]);	

		if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO){
			fprintf(stderr, "error dup2");
			exit(EXIT_FAILURE);
		}		
//		close(fd[1]);
		execlp("ls", "ls", NULL);
	}else{

		printf("%d\n", a[ap]);	

		if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
			fprintf(stderr, "error dup2");
			exit(EXIT_FAILURE);
		}	
		execlp("grep", "grep", "c", NULL);
	}
	


	exit(EXIT_SUCCESS);
}
