#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#define MAX_FILE_NAME_SIZE 100
#define MAX_ARRAY_SIZE 2848
/*
 * WRITTEN BY 3HY
 * 13:12:40 09/04/2024
 *
 * FREE AND OPEN SOURCE USE IF WANTED
 */ 

void dropdown(char **array, int size, char *prompt)
{
	int local_index = 0;
	int local_touch;
	int longest_item = 0;
	for (int i = 0; i < size; i++)
	{
		if (strlen(array[i]) > longest_item)
		{
			longest_item = strlen(array[i]);
		}
	}
		system("clear");
		printf("%s",prompt);
		for (int i = 0; i < size; i++){
			if (i == local_index)
			{
				printf("\033[42;30m%s", array[i]);
				for (int ii = 0; ii < ((longest_item+1) - strlen(array[i])); ii++)
				{
					printf(" ");
				}
				printf("\n\033[0m");
			}
			else
			{
				printf("%s\n", array[i]);
			}
		}
}



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
  	if (d) {
				char *fileList[sizeof(dir->d_name)+MAX_FILE_NAME_SIZE];
    		while ((dir = readdir(d)) != NULL) {
					int flagItemIgnore=0;
					for(int i=0;i<sizeof(ignoreList)/sizeof(ignoreList[0]);i++){
						if(flagItemIgnore!=1){
							if(strcmp(dir->d_name,ignoreList[i])==0){
								flagItemIgnore=1;
							}
						}
					}
					if(flagItemIgnore==0){
						fileCount++;
						fileList[fileCount]=dir->d_name;

					}
    		}
    		closedir(d);
				dropdown(fileList,sizeof(fileCount)/sizeof(fileCount[0]),"test");
  	}
  return(0);
}
