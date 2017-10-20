#include "packages.h"
#include "shellPrototypes.h"
#include "inputPrototype.h"

void main(int argc, char* argv[]){
	char buffer[PATH_MAX+1];
	char savedbuff[PATH_MAX+1];
	char tokbuffer[PATH_MAX+1];
	char* token;
	char* strptr;

	char startingPath[PATH_MAX+1];
	char* ptr = getcwd(startingPath, PATH_MAX+1);

	//if reading from the command line
	if(argc == 1){
		while(1){

			//compare first argument with possible arguments
			//call related function

			strptr = getLine(stdin);
			strcpy(buffer, strptr);
			strcpy(savedbuff, buffer);
			token = strtok(buffer, " \n");
			if(strcmp(token, "quit") == 0){
				quitShell();
			}

			else if(strcmp(token, "wd") == 0){
				printWD();
			}

			else if(strcmp(token, "chwd") == 0){
				token = strtok(NULL, " \n");
				char newBuff[strlen(savedbuff)+1];
				strcpy(newBuff, token);
				if(newBuff[0] == '/'){
					chwdAbsolute(newBuff);
				}
				else{
					chwd(newBuff);
				}
			}
			else if(strcmp(token, "list") == 0){
				shellList(savedbuff, startingPath);
			}
			else if(strcmp(token, "create") == 0){
				shellCreate(savedbuff, startingPath);
			}
		}
	}

	//If you're reading commands from a file
	else if(argc == 2){

		//open file
		FILE* infile = fopen(argv[1], "r");
		if(infile == NULL){
			fprintf(stderr, "Error opening file\n");
			exit(0);
		}

		char* strptr;

		//read each line until null
		while(strcmp((strptr = getLine(infile)), "\0")){

			//parse for command and call related function
			strcpy(buffer, strptr);
			strcpy(savedbuff, buffer);
			token = strtok(buffer, " \n");
			if(strcmp(token, "quit") == 0){
				quitShell();
			}

			else if(strcmp(token, "wd") == 0){
				printWD();
			}

			else if(strcmp(token, "chwd") == 0){
				token = strtok(NULL, " \n");
				char newBuff[strlen(savedbuff)+1];
				strcpy(newBuff, token);
				if(newBuff[0] == '/'){
					chwdAbsolute(newBuff);
				}
				else{
					chwd(newBuff);
				}
			}
			else if(strcmp(token, "list") == 0){
				shellList(savedbuff, startingPath);
			}
			else if(strcmp(token, "create") == 0){
				shellCreate(savedbuff, startingPath);
			}
			else{
				printf("Error: invalid command\n");
			}
		
		}
	}
	else{
		fprintf(stderr, "Error: invalid number of arguments\n");
		exit(0);
	}
}