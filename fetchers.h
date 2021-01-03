//fetchers.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/socket.h>

#define ID_LEN 100

int doi2bibtex (char *doi) {
	char url[100];//, *cmd_str; //"http://api.crossref.org/works/${1}/transform/application/x-bibtex"
	sprintf(url, "http://api.crossref.org/works/%s/transform/application/x-bibtex", doi);
	printf("%s\n", url);
	sprintf(char cmd_str[], "curl -s \"%s\" -w \"\\n\"", url);
	printf("%s\n", cmd_str);
	//system(cmd_str);
	return 0;
}

