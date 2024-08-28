#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY_LENGTH 100


// ( TO_BE_SEARCHED | TO_BE_RETURNED | TO_BE_SEARCHED_FOR ) => VALUE_STRING
#define dict(array1,array2,key) dict_pointer(array1,array2,sizeof(array2)/sizeof(array2[0]),key)
char* dict_pointer(char array1[][MAX_ARRAY_LENGTH],char array2[][MAX_ARRAY_LENGTH],size_t length,char *key){
	for(int i=0;i<length;i++){
		if(strcmp(array1[i],key)==0){
			char* returnKey = array2[i];
			return returnKey;			
		}
	}
	return "Not Found";
}

// ( TO_BE_SEARCHED | TO_BE_RETURNED | TO_BE_SEARCHED_FOR ) => VALUE_INDEX
#define dictIndex(arrayKeys,arrayValues,key) dict_index_pointer(arrayKeys,arrayValues,sizeof(arrayKeys)/sizeof(arrayKeys[0]),key)
int dict_index_pointer(char arrayKeys[][MAX_ARRAY_LENGTH],char arrayValues[][MAX_ARRAY_LENGTH],size_t length,char *key){
	for(int i=0;i<length;i++){
		if(strcmp(arrayKeys[i],key)==0){
			return i;
		}
	}
}

int main(){ 
	
	char array_keys[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH]={
		"Model",
		"Engine",
		"Year",
		"Type",
	};

	char array_values[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH]={
		"Car(tm)",
		"Engine(tm)", 
		"idk like 1999 or somthin", 
		"FUCKIN WAGOON",
	};
	char *indexOf = dict(array_keys,array_values,"Type");
	printf("%s\n",indexOf);
	return 0;
}
