#include <stdio.h>
#include <stdlib.h>

void allocateMatrix(int ***matrix, int width, int height);

int main()
{
    int **maze = NULL, width = 30, height = 20;
    int **fog = NULL;

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
