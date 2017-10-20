#include "packages.h"
#include "createPrototypes.h"

void main(int argc, char* argv[]){
	
	if(argc == 4){
		if(strcmp(argv[1], "-h") == 0){
			createHardLink(argv[2], argv[3]);
		}
		else if(strcmp(argv[1], "-s") == 0){
			createSoftLink(argv[2], argv[3]);
		}
		else{ 
			fprintf(stderr, "Error: invalid command\n"); 
		}
	}
	
	else if(argc == 3){
		if(strcmp(argv[1], "-f") == 0){
			createFile(argv[2]);
		}
		else if(strcmp(argv[1], "-d") == 0){
			createDirectory(argv[2]);
		}
		else{ fprintf(stderr, "Error: invalid command\n"); }
	}
	
	else{
		fprintf(stderr, "Error: invalid number of command line arguments\n");
	}

}