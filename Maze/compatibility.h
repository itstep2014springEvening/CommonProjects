#ifndef COMPATIBILITY_H_INCLUDED
#define COMPATIBILITY_H_INCLUDED

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) \
 || defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)

void clear()
{
    windowsClear();
}

#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux)

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
