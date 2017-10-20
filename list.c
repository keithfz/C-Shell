#include "packages.h"
#include "listPrototypes.h"

void main(int argc, char* argv[]){
	if(argc == 1){
		listCurrent();
	}
	else if(argc == 2){
		if(strcmp(argv[1], "-i")==0){ 
			extraInfo(); 
		}
		else if(strcmp(argv[1], "-h")==0){
			listCurrentHidden();
		}
		else{
			listPath(argv[1]);
		}
	}
	else if(argc == 3){
		if(strcmp(argv[1], "-i")==0){ 
			extraInfoPath(argv[2]); 
		}
		else if(strcmp(argv[1], "-h")==0){
			listPathHidden(argv[2]);
		}
	}
	else{
		fprintf(stderr, "Error: Invalid number of command line arguments\n");
		exit(0);
	}
}