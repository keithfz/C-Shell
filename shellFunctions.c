#include "packages.h"
#include "shellPrototypes.h"

//prints working directory
void printWD(){
	char buffer[PATH_MAX+1];
	char* str = getcwd(buffer, PATH_MAX+1);
	printf("%s\n", buffer);
}

//changes directory given relative filepath
void chwdRelative(char* input){
	errno = 0;
	char buffer[PATH_MAX+1];
	char* str = getcwd(buffer, PATH_MAX+1);
	strcat(buffer, "/");
	strcat(buffer, input);
	chdir(buffer);
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return;
	}
}

//changes directory given absolute filepath
void chwdAbsolute(char* input){
	errno = 0;
	chdir(input);
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return;
	}
}

//changes directory
void chwd(char* input){
	char buffer[PATH_MAX+1];
	strcpy(buffer, input);
	if(buffer[0]=='/'){
		chwdAbsolute(buffer);
	}
	else{
		chwdRelative(buffer);
	}
}

//ends shell
void quitShell(){
	printf("Goodbye.\n");
	exit(0);
}

//forks and executes list
void shellList(char* input, char* startingPath){
	pid_t child;
	int cstatus;
	pid_t c;

	char listLocation[PATH_MAX+1];
	strcpy(listLocation, startingPath);
	strcat(listLocation, "/list");

	if((child = fork()) == 0){
		char buffer[strlen(input)+1];
		strcpy(buffer, input);

		char arguments[5][strlen(input)+1];
		int i = 0;
		char* token = strtok(buffer, " \n");


		while(token!=NULL){
			strcpy(arguments[i], token);
			token = strtok(NULL, " \n");
			i++;
		}
		
		if(i == 1){
			execl(listLocation, "list", NULL);
		}
		else if(i == 2){
			execl(listLocation, "list", arguments[1], NULL);
		}
		else if(i == 3){
			execl(listLocation, "list", arguments[1], arguments[2], NULL);
		}
		else{
			fprintf(stderr, "Incorrect number of arguments\n");
			return;
		}
	}
	else{
		if(child == (pid_t)(-1)){
			fprintf(stderr, "Error: forking error\n");
		}
		else{
			c = wait(&cstatus);
		}
	}
}

//forks and excutes create
void shellCreate(char* input, char* startingPath){
	pid_t child;
	int cstatus;
	pid_t c;

	char createLocation[PATH_MAX+1];
	strcpy(createLocation, startingPath);
	strcat(createLocation, "/create");

	if((child = fork()) == 0){
		char buffer[strlen(input)+1];
		strcpy(buffer, input);

		char arguments[5][strlen(input)+1];

		int i = 0;

		char* token = strtok(buffer, " \n");
		while(token!=NULL){
			strcpy(arguments[i], token);
			token = strtok(NULL, " \n");
			i++;
		}

		if(i == 3){
			execl(createLocation, "create", arguments[1], arguments[2], NULL);
		}
		else if(i == 4){
			execl(createLocation, "create", arguments[1], arguments[2], arguments[3], NULL);
		}
		else{
			fprintf(stderr, "Incorrect number of arguments\n");
			return;
		}
	}
	else{
		if(child == (pid_t)(-1)){
			fprintf(stderr, "Error: forking error\n");
		}
		else{
			c = wait(&cstatus);
		}
	}
}

int getNumberOfArgs(char* input){
	char buffer[strlen(input) + 1];
	int counter = 1;
	int i;
	for(i = 0; i <strlen(input); i++){
		if(buffer[i] == ' '){ 
			counter++;
		}
	}
	return counter;
}











