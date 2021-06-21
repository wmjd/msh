/* William Diebolt (cssc2128), Frank Gomez (cssc2151)
 * CS570, Summer 2020
 * Assignment 2
 * msh.c */

#include "msh.h"
#define LINEBUFSIZE 1024
#include <assert.h>

void prompt(void){
	char user[64];
	getlogin_r(user, 64);
	printf("%s%%", user);
}

void readAndInterpret(void){
	//need to restore stdin in parent at end of this function or it will be lost
	int preserved_stdin = dup(STDIN_FILENO);

	char linebuf[LINEBUFSIZE];
	char * argv[256];
	int ap = 0; //argv pointer points to offset of argv
	
	//state of these variables controls the text processing
	int quoteIsOpen = 0;
	int insideWord = 0;

	int fd[2];
	pid_t res;

	int i; //keep in outer scope
	for(i=0; i<LINEBUFSIZE-1 && (linebuf[i] = getchar()) != '\n'; i++){
		
		if(linebuf[i] == '|' && !quoteIsOpen){
			if(argv[0][0] == 'e' && argv[0][1] == 'x' && argv[0][2] == 'i' && argv[0][3] == 't'){
				exit(EXIT_SUCCESS);
			}
			insideWord = 0;
			argv[ap] = NULL;
			linebuf[i] = 0;
			//error handling
			if(pipe(fd) < 0){
				fprintf(stderr, "ERROR: unable to pipe\n");
				exit(EXIT_FAILURE);
			}if((res = fork()) < 0){
				fprintf(stderr, "ERROR: unable to pipe\n");
				exit(EXIT_FAILURE);
			//parent
			}else if(res > 0){ //reset argv and ap
				for(int j=0; argv[j] != NULL; j++){
					argv[j] = NULL; 	
				}
				ap = 0;
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]); close(fd[1]);
				wait(NULL);
			//child
			}else if(!res){
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]); close(fd[1]);
				if(execvp(*argv, argv) < 0){
					fprintf(stderr, "ERROR: unable to execute %s\n", *argv);
					exit(EXIT_FAILURE);
				}
			}
		}else if(linebuf[i] == '"'){ 
			if(!quoteIsOpen)		   
				argv[ap++] = linebuf+i;
			quoteIsOpen ^= 1;
			insideWord = 1;
		}else if(linebuf[i] == ' '){ 
			if(quoteIsOpen){
				linebuf[i] = ' ';
				insideWord = 1;
			}else{
				linebuf[i] = 0;
				insideWord = 0;
			}
		}else if(!insideWord){
				
				argv[ap++] = linebuf+i;
				insideWord = 1;
		}
	}
	if(argv[0][0] == 'e' && argv[0][1] == 'x' && argv[0][2] == 'i' && argv[0][3] == 't'){
		exit(EXIT_SUCCESS);
	}
	linebuf[i] = 0; //need last word to be a null-terminated string too
	argv[ap] = NULL; //necessary for exec call
	
	/*	execute process	*/
	pid_t pid;
	int status;

	if((pid = fork()) < 0) {
		fprintf(stderr, "%s", "ERROR: unable to fork\n");
		exit(EXIT_FAILURE);
	}

	if(!pid){
		if(execvp(*argv, argv) < 0){
			fprintf(stderr, "ERROR: unable to execute %s\n", *argv);
			exit(EXIT_FAILURE);
		}
	}else{
		wait(NULL);//wait otherwise the terminal will display output after program should have finished
		close(STDIN_FILENO);
		dup2(preserved_stdin, STDIN_FILENO);
	}
}

