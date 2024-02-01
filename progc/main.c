#include "fonction.h"

int main(int argc, char** argv){
	for (int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-t") == 0){
			activer();
		}
		else if(strcmp(argv[i], "-s") == 0){
			activerS();
		}
	}
	return 0;
}
