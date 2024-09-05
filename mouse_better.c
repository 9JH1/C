#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

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

int main() {
    set_raw_mode(STDIN_FILENO);
    enable_mouse_reporting();

    printf("Click anywhere in the terminal to get mouse coordinates.\n");
    printf("Press 'q' to quit.\n");
    fflush(stdout);

    while (1) {
        char buf[6];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
        if (len > 0 && buf[0] == '\033' && buf[1] == '[') {
            if (buf[2] == 'M') {
                // Mouse click event
                if (len >= 6) {
                    int button = buf[3] - ' ' - 1; // Mouse button code
                    int x = buf[4] - ' ' - 1; // Convert from ASCII to coordinate
                    int y = buf[5] - ' ' - 1; // Convert from ASCII to coordinate

                    // Button codes: 0 = left, 1 = middle, 2 = right
                    if (button == 0 || button == 1 || button == 2) {
                        printf("Mouse click at x: %d, y: %d\n", x, y);
                        fflush(stdout);
                    }
                }
            }
        }
        if (buf[0] == 'q') {
            break;
        }
    }

    disable_mouse_reporting();
    reset_mode(STDIN_FILENO);

    return 0;
}

