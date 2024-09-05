#include <stdio.h>
#include <signal.h>



void quitHandler(){
	printf("you REALLY cant quit me!!\n");
}

int main(){

	signal(SIGINT, quitHandler);
	while(1){}	
	return 0;
}
