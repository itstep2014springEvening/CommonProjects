#ifndef COMPATIBILITY_H_INCLUDED
#define COMPATIBILITY_H_INCLUDED

#include <assert.h>


typedef enum _Direction {Up, Down, Right, Left, Mistake} Direction;
Direction getKey();


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) \
 || defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)


#include <conio.h>
Direction getKey()
{
    getch();
    return Up;
}
void windowsClear();

void clear()
{
    windowsClear();
}

#define EMPTY_CELL "."
#define WALL_CELL "\xDB"
#define FOG_CELL "\xB0"
#define HERO_CELL "@"

#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux)

#include <stdio.h>

int linuxGetch();

Direction getKey()
{
    Direction direction = Mistake;
    int key = linuxGetch(), key1, key2;

    switch(key)
    {
        case 97:
            direction = Left;
            break;

        case 115:
            direction = Down;
            break;

        case 119:
            direction = Up;
            break;

        case 100:
            direction = Right;
            break;

        case 27:
            key1 = linuxGetch();
            key2 = linuxGetch();

            if(key1 == 91)
                switch(key2)
                {
                    case 68:
                        direction = Left;
                        break;

                    case 66:
                        direction = Down;
                        break;

                    case 65:
                        direction = Up;
                        break;

                    case 67:
                        direction = Right;
                        break;
                }
    }

    return direction;
}

void linuxClear();

void clear()
{
    linuxClear();
}

#define EMPTY_CELL "."
#define WALL_CELL "\342\226\210"
#define FOG_CELL "\342\226\221"
#define HERO_CELL "@"


#else
#error Not supporting OS
#endif // Os variant

#endif // COMPATIBILITY_H_INCLUDED
