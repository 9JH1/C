#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LENGTH 32
#define MAX_UI_LENGTH 12

void set_input_mode(int enable)
{
	static struct termios oldT, newt;

	if (enable)
	{
		tcgetattr(STDIN_FILENO, &oldT);
		newt = oldT;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
	}
}
char *take_full_input(const char *prompt, int LARGEST_INPUT) {
    char buffer[LARGEST_INPUT];
    char *input;

    // Display the prompt
    printf("%s", prompt);

    // Read the input
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Allocate memory for the input string
        input = malloc(strlen(buffer) + 1);
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return NULL; // Return NULL to indicate an error
        }

        // Copy the input to the allocated memory
        strcpy(input, buffer);
        return input;
    } else {
        // Handle error: Input not successfully read
        fprintf(stderr, "Error reading input.\n");
        return NULL; // Return NULL to indicate an error
    }
}
int take_single_char(char *prompt)
{
	int ch;
	printf("%s",prompt);
	set_input_mode(1);
	ch = getchar();
	set_input_mode(0);
	return ch;
} 
int handle_move()
{
	while (1)
	{
		char ch, chf[100];
		set_input_mode(1);
		ch = getchar();
		set_input_mode(0);
		if (ch == 66)
		{
			return 0;
		}
		else if (ch == 65)
		{
			return 1;
		}
		else if (ch == 10)
		{
			return 4;
		}
		else if (ch == 67)
		{
			return 2;
		}
		else if (ch == 68)
		{
			return 3;
		}
	}
}
char *dropdown(char array[][MAX_LENGTH], int size, char *prompt)
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

	while (1)
	{
		system("clear");
		printf("%s",prompt);
		for (int i = 0; i < size; i++)
		{
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
		local_touch = handle_move();
		if (local_touch == 1)
		{
			local_index--;
		}
		else if (local_touch == 0)
		{
			local_index++;
		}
		if (local_index < 0)
		{
			local_index = size - 1;
		}
		if (local_index > size - 1)
		{
			local_index = 0;
		}
		if (local_touch == 4)
		{
			return array[local_index];
		}
	}
}
	/*
	// ---- EXAMPLE ----
	char local_page[][MAX_LENGTH] = {
		"2",
		"1",
		"5",
	};
	// ^ define a list of answers for the menu

	char *answer = render_ui(local_page, (sizeof(local_page) / sizeof(local_page[0])),"What is 1+1=?\n");
	//                       ^^^^^^^^^^
    //                       call the render_ui function with our array of questions
	// also called is the "(sizeof(local_page) / sizeof(local_page[0]))" this is just giving the function the overall amount of items in the array
	// and the "What is 1+1=?\n" is the prompt that will be showen at the top of the menu

	if(strcmp(answer,"2")==0){
		//    ^^^^^^
		//    the render_ui function returns the string value of what was selected,
		printf("Correct!\n");
		// ^ if the answer is equ to "2" then Correct!
	} else {
		printf("Incorrect!\n");
		// ^ any other answer will result in an Incorrect!
	
	}
	*/
