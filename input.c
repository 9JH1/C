#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
int awaitInputNoEnter(){
	while(1){
		int  keycode;
		struct termios oldT, newT;
		tcgetattr(STDIN_FILENO,&oldT);
		newT = oldT;
		newT.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO,TCSANOW,&newT);

		// take a char
		keycode = getchar();
		tcsetattr(STDIN_FILENO,TCSANOW,&oldT);
		return keycode;
	}
}

int main(){
	while(1){
		char  key = awaitInputNoEnter();
		fflush(stdout);

    		printf("\nYou pressed: '%c' (ASCII code: %d)\n", key, (int)key);
	}
	return 0;
}

