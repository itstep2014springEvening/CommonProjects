#include <stdio.h>
#include <stdlib.h>
#include "compatibility.h"

void allocateMatrix(int ***matrix, int width, int height);
void freeMatrix(int ***matrix, int width, int height);

int main()
{
    int **maze = NULL, width = 30, height = 20;
    int **fog = NULL;

    allocateMatrix(&maze,width,height);
    allocateMatrix(&fog,width,height);

    printf("first\n");
    scanf("%d",&width);
    clear();
    printf("second\n");

    freeMatrix(&fog,width,height);
    freeMatrix(&maze,width,height);


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
