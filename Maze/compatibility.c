#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) \
 || defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)

void windowsClear()
{
    system("cls");
}

#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux)
#include <stdio.h>
#include <termio.h>
#include <unistd.h>

int linuxGetch()
{
    struct termios oldt, newt;
    int key;
    tcgetattr(STDIN_FILENO, &oldt);
    newt=oldt;
    newt.c_lflag &= ~ICANON;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    key = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return key;
}

void linuxClear()
{
    system("clear");
}
#else
#error Not supporting OS
#endif // Os variant
