#include "packages.h"
#include "listPrototypes.h"

//lists all the files in the given path
void list(char* path){

	errno = 0;

	char buffer[PATH_MAX+1];

	DIR *inDirectory = opendir(path);
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}

	struct dirent *entry;

	while((entry = readdir(inDirectory))!=NULL){
		if(errno != 0){
			fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
			exit(0);
		}
		else{
			strcpy(buffer, entry->d_name);
			if(buffer[0] != '.'){
				printf("%s\n", buffer);
			}
		}
	}
	closedir(inDirectory);
}

//gets cwd, calls list
void listCurrent(){
	char buffer[PATH_MAX+1];
	char* cwd;
	cwd = getcwd(buffer, PATH_MAX+1);
	list(cwd);
}

//get filepath, calls list
void listPath(char* path){
	char buffer[PATH_MAX+1];
	strcpy(buffer, path);
	if(buffer[0] == '/'){
		list(path);
	}
	else{
		char temp[PATH_MAX+1];
		char* dirpath = getcwd(temp, PATH_MAX+1);
		strcat(temp, "/");
		strcat(temp, buffer);
		list(temp);
	}
}

//lists hidden files
void listHidden(char* path){
	char buffer[PATH_MAX+1];

	DIR *inDirectory = opendir(path);
	if(inDirectory == NULL){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}

	struct dirent *entry;
	errno = 0;

	while((entry = readdir(inDirectory))!=NULL){
		if(errno != 0){
			fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
			exit(0);
		}
		else{
			strcpy(buffer, entry->d_name);
			if(buffer[0] == '.'){
				printf("%s\n", buffer);
			}
		}
	}
	closedir(inDirectory);
}

//calls listhidden on cwd
void listCurrentHidden(){
	char buffer[PATH_MAX+1];
	char* cwd;
	cwd = getcwd(buffer, PATH_MAX+1);
	listHidden(cwd);
}

//calss listhidden on a given filepath
void listPathHidden(char* path){
	char buffer[PATH_MAX+1];
	strcpy(buffer, path);
	if(buffer[0] == '/'){
		listHidden(path);
	}
	else{
		char temp[PATH_MAX+1]; 
		char* dirpath = getcwd(temp, PATH_MAX+1);
		strcat(temp, "/");
		strcat(temp, buffer);
		listHidden(temp);
	}
}

//lists with extra info
void listExtra(char* path){
	char buffer[PATH_MAX+1];
	errno = 0;

	DIR *inDirectory = opendir(path);
	if(inDirectory == NULL){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}

	struct dirent *entry;
	struct stat myStat;
	errno = 0;

	while((entry = readdir(inDirectory))!=NULL){
		if(errno != 0){
			fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
			exit(0);
		}
		else{
			strcpy(buffer, entry->d_name);
			if(buffer[0] != '.'){
			printf("Name: %s  |  ", buffer);
			
			strcpy(buffer, path);
			strcat(buffer, "/");
			strcat(buffer, entry->d_name);

			stat(buffer, &myStat);
			printf("Size: %d bytes  |  ", myStat.st_size); fflush(stdout);
			printf("Inode: %d  |  ", myStat.st_ino); fflush(stdout);
			int permission = myStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
			printf("Permissions: %o", permission);
		    printf("\n");
		}
		}
	}
	closedir(inDirectory);
}

//gets extra info on cwd
void extraInfo(){
	char buffer[PATH_MAX+1];
	char* cwd;
	cwd = getcwd(buffer, PATH_MAX+1);
	listExtra(cwd);
}

//gets extra info on filepath
void extraInfoPath(char* path){
	char buffer[PATH_MAX+1];
	strcpy(buffer, path);
	if(buffer[0] == '/'){
		listExtra(path);
	}
	else{
		char temp[PATH_MAX+1]; 
		char* dirpath = getcwd(temp, PATH_MAX+1);
		strcat(temp, "/");
		strcat(temp, buffer);
		listExtra(temp);
	}
}
