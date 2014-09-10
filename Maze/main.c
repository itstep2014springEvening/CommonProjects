#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "compatibility.h"

void allocateMatrix(int ***matrix, int width, int height);
void freeMatrix(int ***matrix, int width, int height);
void drawMaze(int **maze, int **fog, int width, int height, int heroX, int heroY);
void generateMaze(int **maze, int width, int height, int *heroX, int *heroY);
void generateFog(int **fog, int width, int height, int heroX, int heroY);

int main()
{
    srand(time(NULL));
    int **maze = NULL, width = 30, height = 20;
    int **fog = NULL;
    int heroX = 5, heroY = 7;

    allocateMatrix(&maze, width, height);
    allocateMatrix(&fog, width, height);

    generateMaze(maze, width, height, &heroX, &heroY);
    generateFog(fog, width, height, heroX, heroY);
    drawMaze(maze, fog, width, height, heroX, heroY);

    freeMatrix(&fog, width, height);
    freeMatrix(&maze, width, height);


    return 0;
}

void allocateMatrix(int ***matrix, int width, int height)
{
    *matrix = (int **) malloc(height * sizeof(int *));

    for(int i = 0; i < height; ++i)
    {
        (*matrix)[i] = NULL;
    }

    for(int i = 0; i < height; ++i)
    {
        (*matrix)[i] = (int *) malloc(width * sizeof(int));
    }
}

void freeMatrix(int ***matrix, int width, int height)
{
    for(int i = 0; i < height; ++i)
    {
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
    }

    free(*matrix);
    *matrix = NULL;
}

void drawMaze(int **maze, int **fog, int width, int height, int heroX, int heroY)
{
    static char symbols [2][4] = {EMPTY_CELL, WALL_CELL};

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            if(fog[i][j] == 1)
            {
                printf("%s", FOG_CELL);
            }
            else
            {
                if(j == heroX && i == heroY)
                {
                    printf("%s", HERO_CELL);
                }
                else
                {
                    printf("%s", symbols[maze[i][j]]);
                }
            }
        }

        printf("\n");
    }
}

void generateMaze(int **maze, int width, int height, int *heroX, int *heroY)
{
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            maze[i][j] = 0; //EMPTY_CELL
        }
    }

    for(int i = 0; i < height; ++i)
    {
        maze[i][0] = 1;
        maze[i][width - 1] = 1;
    }

    for(int i = 0; i < width; ++i)
    {
        maze[0][i] = 1;
        maze[height - 1][i] = 1;
    }

    int perimetr = 2 * (width -2) + 2 * (height - 2);
    int exit = rand() % perimetr;

    if(exit < width-2)
        maze[0][exit+1] = 0;
    else if(exit < 2*(width-2))
        maze[height-1][exit-width+3] = 0;
    else if(exit<2*(width-2)+height-2)
        maze[exit-2*width+5][0]=0;
    else
        maze[exit-2*width-height+7][width-1]=0;

    int countOfWall=(width-2)*(height-2)/2;
    for (int i = 0; i < countOfWall; ++i)
    {
        int wallX=rand()%(width-2)+1;
        int wallY=rand()%(height-2)+1;
        maze[wallY][wallX]=1;
    }
    int flag=1;
    int x,y;
    do
    {
        x=rand()%(width-2)+1;
        y=rand()%(height-2)+1;
        flag=maze[y][x]!=0;
    }while(flag);
    *heroX=x;
    *heroY=y;
}

void generateFog(int **fog, int width, int height, int heroX, int heroY)
{
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            fog[i][j] = 1; //EMPTY_CELL
        }
    }

    fog[heroY][heroX] = 0;
}
