#include "xolib.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define draw(array) (draw_pointer(array))
int draw_pointer(int array[8]){
	int counterIndex=-1;
	for(int i=0;i<3/*nine boxes ofc*/;i++){
		if(i>0){
			printf("\n\n");
		}
		// for each value;
		for(int ii=0;ii<3;ii++){
			// top row;
			char numberChar[20];
			sprintf(numberChar, "%d", counterIndex+2+ii);
			printc(0,0,0,255,255,255," ");
			int alpha=150;
			printc(alpha,alpha,alpha,255,255,255,numberChar);
			printc(0,0,0,255,255,255," ");
			printf(" ");
			
		}
		printf("\n");
		for(int ii=0;ii<3;ii++){
			counterIndex++;
			// middle row;
			printc(0,0,0,255,255,255," ");
			if(array[counterIndex]==0){
				printc(0,0,0,255,255,255," ");
			} else if(array[counterIndex]==1){
				printc(1,10,43,255,255,255,"X");
			} else if(array[counterIndex]==2){
				printc(255,0,0,255,255,255,"O");
			}
			printc(0,0,0,255,255,255," ");
			printf(" ");
		}
		// print the bottom row
		printf("\n");
		for(int ii=0;ii<3;ii++){
			printc(0,0,0,255,255,255,"   ");
			printf(" ");
		}

				
	}
	printf("\n");
	// check rows
	for (int i = 0; i < 9; i += 3) {
    		if (array[i] != 0 && array[i] == array[i + 1] && array[i + 1] == array[i + 2]) {
        		return array[i];
    		}
	}
	//check collums
	for (int i = 0; i < 3; i++) {
    		if (array[i] != 0 && array[i] == array[i + 3] && array[i + 3] == array[i + 6]) {
        		return array[i]; // Return the winner (1 or 2)
    		}
	}
	// Top-left to bottom-right diagonal
	if (array[0] != 0 && array[0] == array[4] && array[4] == array[8]) {
	    return array[0]; // Return the winner (1 or 2)
	}

	// Top-right to bottom-left diagonal
	if (array[2] != 0 && array[2] == array[4] && array[4] == array[6]) {
    		return array[2]; // Return the winner (1 or 2)
	}
	int emptySpaces=0;
	for(int i=0;i<9;i++){
		if(array[i] == 0){
			emptySpaces++;
		}
	}
	if(emptySpaces==0){
		return 0;
	}
	return 4;
}

int main(){
	system("clear");
	int array[9]={
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	};
	// can be a value from 0-i
	int turn=1;
	int isClear=0;
	// 1=X 2=O
	draw(array);
	while(1){
		printf("Player %d's turn\n",turn);
		char* input=take_full_input("Enter A Box: ",4);
		if(strcmp(input,"hl")==0){
			printf("Guide:\n123\n456\n789\nenter a number corasponding to the unit you want to tag,\n");
		} else {
			int inputNumber = atoi(input)-1;
			//array[inputNumber]=1;
			if(turn==1){
				if(array[inputNumber]==0){
					array[inputNumber]=1;
					turn=2;		
					isClear=1;
				} else {
					printf("Please pick an empty square\n");
					isClear=0;
				}
			} else if(turn==2){
				if(array[inputNumber]==0){
					array[inputNumber]=2; 
					turn=1;
					isClear=1;
				} else {
					printf("Please pick an empty square\n");
					isClear=0;
				}
			}
			if(isClear==1){
					system("clear");
					int result = draw(array);
					if(result==1){
						printf("Player 1 Has Won!!\n");
						exit(0);
					} else if(result==2){
						printf("Player 2 has Won!!\n");
						exit(0);
					} else if(result==0){
						printf("Players Have Tied\n");
						exit(0);
					}
				}
			

		}

	}

	return 0;
}
