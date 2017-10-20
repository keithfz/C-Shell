#include "packages.h"

//Gets target filepath, creates file
void createFile(char* filepath){
	errno = 0;
	char buffer[strlen(filepath)+1];
	strcpy(buffer, filepath);

	if(buffer[0] == '/'){
		creat(buffer, 0640);
	}
	else{
		char temp[PATH_MAX+1];
		char* str = getcwd(temp, PATH_MAX+1);
		strcat(temp, "/");
		strcat(temp, buffer);
		creat(temp, 0640);
	}
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}
}

//Gets target filepath, creates directory
void createDirectory(char* filepath){
	errno = 0;
	char buffer[strlen(filepath)+1];
	strcpy(buffer, filepath);

	if(buffer[0] == '/'){
		mkdir(buffer, 0750);
	}
	else{
		char temp[PATH_MAX+1];
		char* str = getcwd(temp, PATH_MAX+1);
		strcat(temp, "/");
		strcat(temp, buffer);
		mkdir(temp, 0750);
	} 
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}
}

//gets filepaths, makes new link
void createHardLink(char* oldname, char* linkname){
	errno = 0;
	int success;
	char linkpath[PATH_MAX + 1];
	char oldpath[PATH_MAX + 1];

	char buff1[strlen(oldname) + 1];
	strcpy(buff1, oldname);

	char buff2[strlen(linkname) + 1];
	strcpy(buff2, linkname);

	if(buff1[0] == '/'){
		strcpy(oldpath, buff1);
	}
	else{
		char* str = getcwd(oldpath, PATH_MAX + 1);
		strcat(oldpath, "/");
		strcat(oldpath, oldname);
	}

	if(buff2[0] == '/'){
		strcpy(linkpath, linkname);
	}
	else{
		char* str2 = getcwd(linkpath, PATH_MAX + 1);
		strcat(linkpath, "/");
		strcat(linkpath, linkname);
	}

	link(oldpath, linkpath);
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}

}

//gets filepaths creates softlink
void createSoftLink(char* oldname, char* linkname){
	errno = 0;
	int success;
	char linkpath[PATH_MAX + 1];
	char oldpath[PATH_MAX + 1];

	char buff1[strlen(oldname) + 1];
	strcpy(buff1, oldname);

	char buff2[strlen(linkname) + 1];
	strcpy(buff2, linkname);

	if(buff1[0] == '/'){
		strcpy(oldpath, buff1);
	}
	else{
		char *str = getcwd(oldpath, PATH_MAX + 1);
		strcat(oldpath, "/");
		strcat(oldpath, oldname);
	}

	if(buff2[0] == '/'){
		strcpy(linkpath, linkname);
	}
	else{
		char *str2 = getcwd(linkpath, PATH_MAX + 1);
		strcat(linkpath, "/");
		strcat(linkpath, linkname);
	}

	symlink(oldpath, linkpath);
	if(errno != 0){
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(0);
	}
}













