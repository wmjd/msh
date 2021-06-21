/* William Diebolt (cssc2128), Frank Gomez (cssc2151)
 * CS570, Summer 2020
 * Assignment 2
 * main.c */

#include "msh.h"

int main(void){

	for(;;){
		prompt();
		readAndInterpret();
	}

	exit(EXIT_SUCCESS);
}
