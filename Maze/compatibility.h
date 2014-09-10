#ifndef COMPATIBILITY_H_INCLUDED
#define COMPATIBILITY_H_INCLUDED

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) \
 || defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)

void clear()
{
    windowsClear();
}

#define EMPTY_CELL "."
#define WALL_CELL "\xDB"
#define FOG_CELL "\xB0"
#define HERO_CELL "\xFE"

#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux)

void clear()
{
    linuxClear();
}

#else
#error Not supporting OS
#endif // Os variant

#endif // COMPATIBILITY_H_INCLUDED
