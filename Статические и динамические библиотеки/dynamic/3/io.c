#include "io.h"


static void clear_screen()
{
    printf("\033[2J");
    printf("\033[H");
}

void disable_buffered_input()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_buffered_input()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void menu(int32_t selected)
{
    int32_t num_options = sizeof(options) / sizeof(options[0]);

    clear_screen();
    printf("\033[1;34mМеню:\033[0m\n");

    for (size_t i = 0; i <  num_options; i++)
    {

        if (i == selected)
        {
            printf("\033[1;34m> %s\033[0m\n", options[i]);
        }
        else
        {
            printf("  %s\n", options[i]);
        }
    }
}
