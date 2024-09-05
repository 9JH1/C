#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#define MAX_ARRAY_SIZE 100

void clearScreen()
{
	system("clear");
}

int awaitInputNoEnter()
{
	while (1)
	{
		int keycode;
		struct termios oldT, newT;
		tcgetattr(STDIN_FILENO, &oldT);
		newT = oldT;
		newT.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newT);

		// take a char
		keycode = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
		return (char)keycode;
	}
}

void printc(
	int foreground_r,int foreground_g,int foreground_b,int background_r,int background_g,int background_b,
	char *text)
{
	/* concatanate into one string */
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%s\033[0m",
		   foreground_r,
		   foreground_g,
		   foreground_b,
		   background_r,
		   background_g,
		   background_b,
		   text);
}

int getScreen(int rows, int cols)
{

	struct winsize window;
	ioctl(0, TIOCGWINSZ, &window);
	cols = window.ws_col;
	rows = window.ws_row;
	return rows, cols;
}

char *take_full_input(const char *prompt, int LARGEST_INPUT)
{
	char buffer[LARGEST_INPUT];
	char *input;

	// Display the prompt
	printf("%s", prompt);

	// Read the input
	if (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
		// Remove newline character if present
		buffer[strcspn(buffer, "\n")] = '\0';

		// Allocate memory for the input string
		input = malloc(strlen(buffer) + 1);
		if (input == NULL)
		{
			fprintf(stderr, "Memory allocation failed.\n");
			return NULL; // Return NULL to indicate an error
		}

		// Copy the input to the allocated memory
		strcpy(input, buffer);
		return input;
	}
	else
	{
		// Handle error: Input not successfully read
		fprintf(stderr, "Error reading input.\n");
		return NULL; // Return NULL to indicate an error
	}
}

char *concat(const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

// sneaky sneaky
#define dropdown(array, prompt) dropdown_pointer(array, sizeof(array) / sizeof(array[0]), prompt);
char *dropdown_pointer(char array[][MAX_ARRAY_SIZE], int size, char *prompt)
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
		clearScreen();
		printf("%s", prompt);
		for (int i = 0; i < size; i++)
		{
			if (i == local_index)
			{
				printf("\033[42;30m%s", array[i]);
				for (int ii = 0; ii < ((longest_item + 1) - strlen(array[i])); ii++)
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
}

#define contains(text, array) (contains_pointer(text, array, sizeof(array) / sizeof(array[0])))
int contains_pointer(char *text, char array[][MAX_ARRAY_SIZE], size_t array_size)
{
	for (int i = 0; i < array_size; i++)
	{
		;
		if (strcmp(text, array[i]) == 0)
		{
			return 0;
		}
	}
	return 1;
}



void enable_mouse_reporting() {
    printf("\033[?1003h"); // Enable mouse reporting
    fflush(stdout);
}

void disable_mouse_reporting() {
    printf("\033[?1003l"); // Disable mouse reporting
    fflush(stdout);
}

void set_raw_mode(int fd) {
    struct termios term;
    tcgetattr(fd, &term);
    term.c_lflag &= ~(ECHO | ICANON); // Disable canonical mode and echo
    tcsetattr(fd, TCSANOW, &term);
}

void reset_mode(int fd) {
    struct termios term;
    tcgetattr(fd, &term);
    term.c_lflag |= (ECHO | ICANON); // Enable canonical mode and echo
    tcsetattr(fd, TCSANOW, &term);
}

void quitHandler(){
    disable_mouse_reporting();
    reset_mode(STDIN_FILENO);
    exit(0);
}

int awaitMouseClick() {
    set_raw_mode(STDIN_FILENO);
    enable_mouse_reporting();
	signal(SIGINT, quitHandler);
    fflush(stdout);
    while (1) {
        char buf[6];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
        if (len > 0 && buf[0] == '\033' && buf[1] == '[') {
            if (buf[2] == 'M') {
                if (len >= 6) {
                    int button = buf[3] - ' ' - 1; // Mouse button code
                    int x = buf[4] - ' ' - 1; // Convert from ASCII to coordinate
                    int y = buf[5] - ' ' - 1; // Convert from ASCII to coordinate

                    // Button codes: 0 = left, 1 = middle, 2 = right
                    if (button == 0 || button == 1 || button == 2) {
                        return x,y;
                    }
                }
            }
        }
    }

    disable_mouse_reporting();
    reset_mode(STDIN_FILENO);

    return 0;
}

void awaitClickPreciseStatic(int xF, int yF, void (*callHandler)()){
    set_raw_mode(STDIN_FILENO);
    enable_mouse_reporting();
    fflush(stdout);
    while (1) {
        fflush(stdout);
        char buf[6];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
        if (len > 0 && buf[0] == '\033' && buf[1] == '[') {
            if (buf[2] == 'M') {
                if (len >= 6) {
                    int button = buf[3] - ' ' - 1; // Mouse button code
                    int x = buf[4] - ' ' - 1; // Convert from ASCII to coordinate
                    int y = buf[5] - ' ' - 1; // Convert from ASCII to coordinate
                    if (button == 0 || button == 1 || button == 2) {
                        if(xF == x && yF == y){
                            disable_mouse_reporting();
                            reset_mode(STDIN_FILENO);
                            callHandler();
                            break;
                        }
                    }
                }
            }
        }
    }
}