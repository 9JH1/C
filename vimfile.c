#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "xolib.c"
#define MAX_FILE_NAME_SIZE 100
#define MAX_ARRAY_SIZE 2848
/*
 * WRITTEN BY 3HY
 * 13:12:40 09/04/2024
 *
 * FREE AND OPEN SOURCE USE IF WANTED
 */ 

int main(){

	char ignoreList[][100]={
		".",
		"..",
		".git",	
	};

	DIR *d;
  struct dirent *dir;
  d = opendir(".");
	
	int fileCount=0;
	int largestTitle=0;
	char *fileList[sizeof(d)*10];
		if (d) {
    while ((dir = readdir(d)) != NULL) {
			int flagItemIgnore=0;
			for(int i=0;i<sizeof(ignoreList)/sizeof(ignoreList[0]);i++){
				if(flagItemIgnore!=1){
					if(strcmp(dir->d_name,ignoreList[i])==0){
						flagItemIgnore=1;
					}
				}
			}

			// add the filtered items
			if(flagItemIgnore==0){	
				fileList[fileCount]=dir->d_name;
				int titleSize=strlen(dir->d_name);
				if(titleSize>largestTitle){
					largestTitle=titleSize;
				}
				fileCount++;
			}
    }
		// finaly close the dir
    closedir(d);
	}
	int indexCount=0;
	largestTitle+=2;
	draw:
	
   	system("clear");
	printf("╭");
	// print inner
	printf("─%s",fileList[indexCount],indexCount);
	for(int i=0;i<largestTitle-strlen(fileList[indexCount])+1;i++){
		printf("─");
	}
	//print the top right corner
	printf("╮\n");
	// ill coime back to this
	for(int i=0;i<fileCount;i++){
		int lineSize=largestTitle-strlen(fileList[i])+1;
		printf("│ ");
		if(indexCount==i){
			printf("-> ");
			// remove the chars for the ->
			lineSize-=3; 			
		}
		printf("%s",fileList[i]);
		for(int ii=0;ii<lineSize;ii++){
			printf(" ");
		}
		printf("│\n");
	}
	// print the last line :(
	printf("╰");
	for(int i=0;i<largestTitle+2;i++){
		printf("─");
	}
	printf("╯\n");
	int input=awaitInputNoEnter();
	if(input==119){
		indexCount--;
	} else if (input==115){
		indexCount++;
	} else if(input==10){
		char *finalCommand = concat("vim ",fileList[indexCount]); 
		system(finalCommand);

		
	}
	if(indexCount>fileCount-1){
		indexCount=0;
	} else if(indexCount<0){
		indexCount=fileCount-1;
	}
	goto draw;
	return(0);
}
