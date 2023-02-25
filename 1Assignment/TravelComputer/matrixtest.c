#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // int num_rows =10, i, j;
    // int **matrix = malloc(num_rows * sizeof(int *));
    // for (i = 0; i < num_rows; i++) {
    //     matrix[i] = malloc(3 * sizeof(int));
    // }

    // printf("AAAAAAAAAAA\n");

    // matrix[0][1]= 1;
    // matrix[0][2]= 1;
    // matrix[8][2]= 1;
    // matrix[3][0]= 1;
    // matrix[3][1]= 1;
    // matrix[3][2]= 1;

    // for (i = 0; i < num_rows; i++) {
    //     for (j = 0; j < 3; j++) {
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    char str[80] = "0 1 3";
    const char s[2] = " ";
    char *token;
    char *city;

    token = strtok(str, s);

    printf(" 1 %s\n",token);
    
    city = strtok(str, s);
    printf(" 2 %s\n",city);

    token = strtok(NULL, s);

    printf(" 3 %s\n",token);
    printf(" 4 %s\n",city);


    return 0;
}