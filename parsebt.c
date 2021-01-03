#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl.curl.h>

#define FSIZE 2000
#define MAXSTACK 10
#define RESET 0
//#define INFIELDVAL
char fname[200];// = "S0025556411001556.bib";

char newkey[] = "newkey";

int stack_len = 0;
int stack[MAXSTACK];
int infieldval=0;
int inkey=0;
int indquotes = 0;
int temp;
int changekey=1;
//void del_whitespace(void) {
//	int c;
//	while ((c=getchar()) == ' ') {
//	}	
//}

//int match_delim(int c) {
//	if ((c == '}') && (stack[stack_len] == '{')) {
//	} else if ((c == '"') && (stack[stack_len] == '{')) {
//	}
//}

int tstream(void) {
	int c;
	while ((c=getc(stdin)) != EOF) {
		if (c == '@') {
			printf("Entry type is: ");
		} else if ((c == '{') && (stack_len == 0)){
			printf("\n");
			printf("Key is: ");
			stack[stack_len++] = c;
			// putchar(c);
			inkey=1;
			if (changekey) {
				printf("%s", newkey);
			}
		} else if (c == '}' && (stack[stack_len] == '{')) {
			stack_len--;
			putchar(c);
			//if (stack_len == 0) {
			//	break;
			//}
		} else if (c == ','){
			//if (inkey){;}
			inkey = RESET;
			infieldval = RESET;
			if (indquotes) {
				printf("COMMA");
			} else {
				printf("SEP");
			}
			putchar(c);
			//c=getchar();
			//temp = c;
		} else if (c == '='){
			printf("EQ");
			putchar(c);
			infieldval = 1;
		} else if (c == '\"'){
			putchar(c);
			indquotes = 1 - indquotes;
		} else if (inkey && changekey){
			;
		} else {
			putchar(c);
		}
	}
	return 0;
}

int main (void) {
	//printf("%s\n", readfts(fname));
	tstream();
	printf("\n");
	return 0;
}

//int check_delims(){
//}

//struct btfields {
//	char title[200];
//	char author[200];
//	int year[4];
//};
//
//struct entry {
//	char entry_type[50];
//	char key[50];
//	struct btfields fields;
//};
//
//void promptfname(){
//	
//}

//char *readfts(char *filename) {
//	static char text[FSIZE]; //= malloc(sizeof(char)*FSIZE);
//	FILE *fp = fopen(filename, "r");
//	if(fp == NULL) {
//		perror("Error in opening file");
//	}
//	int i = 0;
//	char c;
//	while(feof(fp) == 0){
//		c = fgetc(fp);
//		text[i] = c;
//		i++;
//	}
//	fclose(fp);
//	return text;
//}

