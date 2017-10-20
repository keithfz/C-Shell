#include "packages.h"
//Reads line from file, returns null terminated string
char* getLine(FILE* stream){
	int count = 0;

	char *str = (char *) malloc(sizeof(char)*1024);

	if(fgets(str, 1024, stream) == NULL){
		return "\0";
	}
	else{
		return str;
	}
}