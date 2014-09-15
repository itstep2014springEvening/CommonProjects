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
void drawMaze(Matrix maze, Matrix fog, Position hero);
void generateMaze(Matrix maze, Position *hero);
void generateFog(Matrix fog, Position hero);

int main()
{
    srand(time(NULL));
    Matrix maze = {NULL, 0, 0};
    Matrix fog = {NULL, 0, 0};
    int width = 30, height = 20;
    Position hero;


    allocateMatrix(&maze, width, height);
    allocateMatrix(&fog, width, height);

    generateMaze(maze, &hero);
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

void generateMaze(Matrix maze, Position *hero)
{
    for(int i = 0; i < maze.height; ++i)
    {
        for(int j = 0; j < maze.width; ++j)
        {
            maze.matrix[i][j] = 0; //EMPTY_CELL
        }
    }

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

    int perimetr = 2 * (maze.width - 2) + 2 * (maze.height - 2);
    int randCell = rand() % perimetr;

    if(randCell < maze.width - 2)
        maze.matrix[0][randCell + 1] = 0;
    else if(randCell < 2 * (maze.width - 2))
        maze.matrix[maze.height - 1][randCell - maze.width + 3] = 0;
    else if(randCell < 2 * (maze.width - 2) + maze.height - 2)
        maze.matrix[randCell - 2 * maze.width + 5][0] = 0;
    else
        maze.matrix[randCell - 2 * maze.width - maze.height + 7][maze.width - 1] = 0;

    int countOfWall = (maze.width - 2) * (maze.height - 2) / 2;

    for(int i = 0; i < countOfWall; ++i)
    {
        Position wall;
        wall.x = rand() % (maze.width - 2) + 1;
        wall.y = rand() % (maze.height - 2) + 1;
        maze.matrix[wall.y][wall.x] = 1;
    }

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
    for(int i = 0; i < fog.height; ++i)
    {
        for(int j = 0; j < fog.width; ++j)
        {
            fog.matrix[i][j] = 1; //EMPTY_CELL
        }
    }

    fog.matrix[hero.y][hero.x] = 0;
}
