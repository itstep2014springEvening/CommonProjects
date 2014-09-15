#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "compatibility.h"

typedef struct _Position
{
    int x, y;
} Position;

typedef struct _Matrix
{
    int **matrix;
    int width;
    int height;
} Matrix;

void allocateMatrix(Matrix *a, int width, int height);
void freeMatrix(Matrix *a);
void fillmatrixWithValue(Matrix a, int value);
void drawMaze(Matrix maze, Matrix fog, Position hero);
void generateMaze(Matrix maze, Position *hero, Position *exit);
void generateFog(Matrix fog, Position hero);

int main()
{
    srand(time(NULL));
    Matrix maze = {NULL, 0, 0};
    Matrix fog = {NULL, 0, 0};
    int width = 30, height = 20;
    Position hero, exit;


    allocateMatrix(&maze, width, height);
    allocateMatrix(&fog, width, height);

    generateMaze(maze, &hero, &exit);
    generateFog(fog, hero);
    drawMaze(maze, fog, hero);

    freeMatrix(&fog);
    freeMatrix(&maze);


    return 0;
}

void allocateMatrix(Matrix *a, int width, int height)
{
    a->matrix = (int **) malloc(height * sizeof(int *));

    for(int i = 0; i < height; ++i)
    {
        a->matrix[i] = NULL;
    }

    for(int i = 0; i < height; ++i)
    {
        a->matrix[i] = (int *) malloc(width * sizeof(int));
    }

    a->width = width;
    a->height = height;
}

void freeMatrix(Matrix *a)
{
    for(int i = 0; i < a->height; ++i)
    {
        free(a->matrix[i]);
        a->matrix[i] = NULL;
    }

    free(a->matrix);
    a->matrix = NULL;
}

void fillmatrixWithValue(Matrix a, int value)
{
    for(int i = 0; i < a.height; ++i)
    {
        for(int j = 0; j < a.width; ++j)
        {
            a.matrix[i][j] = 0;
        }
    }
}


void drawMaze(Matrix maze, Matrix fog, Position hero)
{
    static char symbols [2][4] = {EMPTY_CELL, WALL_CELL};

    for(int i = 0; i < maze.height; ++i)
    {
        for(int j = 0; j < maze.width; ++j)
        {
            if(fog.matrix[i][j] == 1)
            {
                printf("%s", FOG_CELL);
            }
            else
            {
                if(j == hero.x && i == hero.y)
                {
                    printf("%s", HERO_CELL);
                }
                else
                {
                    printf("%s", symbols[maze.matrix[i][j]]);
                }
            }
        }

        printf("\n");
    }
}

void generateBorder(Matrix maze);
Position generateExit(int width, int height);
void generateWalls(Matrix maze);
void generateHero(Matrix maze, Position *hero);

void generateMaze(Matrix maze, Position *hero, Position *exit)
{
    fillmatrixWithValue(maze, 0);
    generateBorder(maze);

    *exit = generateExit(maze.width, maze.height);
    maze.matrix[exit->y][exit->x] = 0;

    generateWalls(maze);
    generateHero(maze,hero);
}

void generateBorder(Matrix maze)
{
    for(int i = 0; i < maze.height; ++i)
    {
        maze.matrix[i][0] = 1;
        maze.matrix[i][maze.width - 1] = 1;
    }

    for(int i = 0; i < maze.width; ++i)
    {
        maze.matrix[0][i] = 1;
        maze.matrix[maze.height - 1][i] = 1;
    }
}

Position generateExit(int width, int height)
{
    int perimetr = 2 * (width - 2) + 2 * (height - 2);
    int randCell = rand() % perimetr;
    Position exit;

    if(randCell < width - 2)
    {
        exit.x = randCell + 1;
        exit.y = 0;
    }
    else if(randCell < 2 * (width - 2))
    {
        exit.x = randCell - width + 3;
        exit.y = height - 1;
    }
    else if(randCell < 2 * (width - 2) + height - 2)
    {
        exit.x = 0;
        exit.y = randCell - 2 * width + 5;
    }
    else
    {
        exit.x = width - 1;
        exit.y = randCell - 2 * width - height + 7;
    }

    return exit;
}

void generateWalls(Matrix maze)
{
    int countOfWall = (maze.width - 2) * (maze.height - 2) / 2;

    for(int i = 0; i < countOfWall; ++i)
    {
        Position wall;
        wall.x = rand() % (maze.width - 2) + 1;
        wall.y = rand() % (maze.height - 2) + 1;
        maze.matrix[wall.y][wall.x] = 1;
    }
}

void generateHero(Matrix maze, Position *hero)
{
    int flag = 1;
    int x, y;

    do
    {
        x = rand() % (maze.width - 2) + 1;
        y = rand() % (maze.height - 2) + 1;
        flag = maze.matrix[y][x] != 0;
    } while(flag);

    hero->x = x;
    hero->y = y;
}

void generateFog(Matrix fog, Position hero)
{
    fillmatrixWithValue(fog,0);
    fog.matrix[hero.y][hero.x] = 0;
}
