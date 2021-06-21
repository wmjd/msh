#include "../msh.h"

/*	the call to printf gets written-over in the terminal??	*/


int main(void){
	char * argv[64];
	char * arg0 = "whoami";
	argv[0] = arg0;
	argv[1] = NULL;
	printf("%s", argv[0]);
	execvp(*argv, argv);
	

	return 0;
}
