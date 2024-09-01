#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 3

#define contains(text, array) (contains_pointer(text, array, sizeof(array)/sizeof(array[0])))
int contains_pointer(char *text, char array[][MAX_ARRAY_SIZE], size_t array_size){
	for(int i=0;i<array_size;i++){;
		if(strcmp(text,array[i])==0){
			return 0;
		}
		
	}
	return 1;
}

int main(int argc, char* argv[]){
	
	// if empty arguments
	if(argc < 1){
		exit(0);
	}

	for(int i=0;i<argc;i++){
		// skip the first item
		if(i>0){
			// handling
			if(i==1){
				// this should be a code telling us
				// what calculation is wanted
				char allowed[][MAX_ARRAY_SIZE]={
					"O",
					"H",
					"A",
				};
				if(contains(argv[i],allowed)==0){
							printf("works");
						} else {
							printf("[ERROR] - Mode Argument Failed\nUSAGE trig [O,H,A] [A,S]");
						}
			}
		}
					
	}

	return 0;
}
