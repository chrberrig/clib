//chbibkey.c

#include <stdio.h>
#include <unistd.h>
//#include <string.h>

#define MAX_BIBLEN 2000
const int alloc_bibtex = MAX_BIBLEN;
static char bibtex[MAX_BIBLEN];

int main(int argc, char **argv) {
	//*char bibfilename[alloc_file];

	// char key[alloc];
	//if (access(argv[2], F_OK) == 0) {
	int i;
	printf("%d\n", argc);
	for (i=0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	printf("before_if\n");
	if (argc == 3) {
		// printf("bibfile %s exists\n", argv[2]);
	
		printf("in_arg_condition\n");
		printf("argv[2] is %s\n", argv[2]);
		//if (strlen(argv[0]) >= MAX_BIBLEN){
		//	fprintf(stderr, "%s is too long!\n");
		//}
		//else {
		//	//strcpy(bibtex, argv[0]);
		//	bibtex = argv[2];
		//}
		bibtex = argv[2];
		//bibfilename = argv[2];
		printf("bibtex %s exists as argv\n", bibtex);
	} 
	else {
		// printf("file dont exist\n");
		printf("in_pipe_condition\n");
		fgets(bibtex, alloc_bibtex, stdin);
		// This is waht you want to do if you read from file:
		//fgets(bibfilename, alloc_file, stdin);
		printf("bibtex %s exists as stdin\n", bibtex);
	}

	
	// char key = argv[1];
	// printf("%s\n", argv[1]);

	//int i;
	//for (i=0; i < argc; i++) {
	//	printf("%s\n", argv[i]);
	//}
	return 0;
}

//int main

