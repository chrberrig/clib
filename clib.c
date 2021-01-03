//clib.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <expat.h>
//#include <libxml/parser.h>
#include <sys/socket.h>

#include "fetchers.h"
//#include "parsebt.h"


#define MAX_BIBLEN 2000
const int alloc_bibtex = MAX_BIBLEN;
const int alloc_key = MAX_BIBLEN/10;

char bibtex[MAX_BIBLEN];

struct datafield {
	char *field_name;
	char *field_val;
};

struct bibtex_entry {
	char entry_type[50];
	char key[50];
	struct datafield *datafields[];
	/*
	char authors[20][50]; //[number of authors][author namelength]
	char title[200];
	char id[200];
	char publisher[200];
	char journal[200];
	char year[20];
	char date[20];
	*/
};

/*
int parse_bibtex(char *bibtex) {
}
*/

int get_main_arg(int argc, char **argv) {
	char input[MAX_BIBLEN];
	if (argc == 3) {
		if (strlen(argv[2]) >= MAX_BIBLEN){
			fprintf(stderr, "%s is too long!\n");
		}
		else {
			strcpy(bibtex, argv[2]);
		}
	} 
	else {
		fgets(bibtex, alloc_bibtex, stdin);
		printf("bibtex %s exists as stdin\n", bibtex);
	}

	return 0;
}


int import_bibtex(int argc, char **argv) {
	char key[alloc_key];
	//if (access(argv[2], F_OK) == 0) {
	//int i;
	//printf("%d\n", argc);
	//for (i=0; i < argc; i++) {
	//	printf("%s\n", argv[i]);
	//}

	printf("argv[1] (key) is %s\n", argv[1]);
	if (argc == 3) {
		if (strlen(argv[2]) >= MAX_BIBLEN){
			fprintf(stderr, "%s is too long!\n");
		}
		else {
			strcpy(bibtex, argv[2]);
		}
	} 
	else {
		fgets(bibtex, alloc_bibtex, stdin);
		printf("bibtex %s exists as stdin\n", bibtex);
	}

	return 0;
}

int change_bibkey(int argc, char **argv) {
	char bibtex[MAX_BIBLEN];
	char key[alloc_key];
	//if (access(argv[2], F_OK) == 0) {
	//int i;
	//printf("%d\n", argc);
	//for (i=0; i < argc; i++) {
	//	printf("%s\n", argv[i]);
	//}

	printf("argv[1] (key) is %s\n", argv[1]);
	if (argc == 3) {
		if (strlen(argv[2]) >= MAX_BIBLEN){
			fprintf(stderr, "%s is too long!\n");
		}
		else {
			strcpy(bibtex, argv[2]);
		}
	} 
	else {
		fgets(bibtex, alloc_bibtex, stdin);
		printf("bibtex %s exists as stdin\n", bibtex);
	}

	return 0;
}

int main(int argc, char **argv){
	int option;
	// put ':' at the starting of the string so compiler can distinguish between '?' and ':'
	while((option = getopt(argc, argv, ":D:f:k:h")) != -1){ //get option from the getopt() method
		switch(option){
			//For option i, r, l, print that these are options
			case 'D':
				doi2bibtex(optarg);
			case 'h':
				printf("Help: %c\n");
			case 'k':
				printf("Given Option: %c\n", option);
				break;
			case 'f': //here f is used for some file name
				printf("Given File: %s\n", optarg);
				break;
			case ':':
				printf("option needs a value\n");
				break;
			case '?': //used for some unknown options
				printf("unknown option: %c\n", optopt);
				break;
		}
	}
	for(; optind < argc; optind++){ //when some extra arguments are passed
	   printf("Given extra arguments: %s\n", argv[optind]);
	}
}

