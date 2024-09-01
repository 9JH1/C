#include <stdio.h>

#define MAX_ARRAY_SIZE 100 

int strcmp(char* value1,char* value2){
	char *value1_size = value1;
	int value1_length = 0;
	while(*value1_size != '\0'){
		value1_size++;
		value1_length++;
	}
	char *value2_size = value2;
	int value2_length = 0;
	while(*value2_size != '\0'){
		value2_size++;
		value2_length++;
	}
	if(value1_length != value2_length){
		// values are obviouly different
		return 1;
	}
	// check char by char
	// FU <string.h>
	for(int i=0;i<value1_length;i++){
		if(value1[i] != value2[i]){
			return 1;
		}
	}
	return 0;
}
#define betterDict(array,value) better_dict_pointer(array,value,((sizeof(array[0][0])/sizeof(array[0][0][0]))/2)+1)
char* better_dict_pointer(char* array[][MAX_ARRAY_SIZE],char *value,size_t size){
	// split the dict into two
	char **array_keys = array[0];
	char **array_values = array[1];
	for(int i=0;i<size;i++){
		if(strcmp(array_keys[i],value)==0){
			// return item if found
			return array_values[i];
		}
	}
	return "NULL";
}

int main(){
		char* dict[][MAX_ARRAY_SIZE] = {
			{"model", "type",  "color",       "year"},
			{"HONDA", "sedan", "tardis_blue", "1997"}
		};
		char* out = betterDict(dict,"jlajkaj");
		printf("%s\n",out);
		return 0;
}
