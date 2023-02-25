#include"queue.h"
#include<omp.h>

#define MAX_LINE_LENGTH 10
int **matrix;


// Defines the cost between two cities
typedef struct
{
	unsigned short originCity;
	unsigned short destCity;
	unsigned short cost;
} travelCost;

//compares the travel cost bwtween two cities
char compare_elements(void* a, void* b) {
    travelCost* travelCost_a = (travelCost*)a;
    travelCost* travelCost_b = (travelCost*)b;

    if (travelCost_a->cost < travelCost_b->cost) {
        return -1;
    } else if (travelCost_a->cost > travelCost_b->cost) {
        return 1;
    } else {
        return 0;
    }
}

// prints the arguments received
void argumentSumary(int nrArgs, char *args[])
{
    printf("%d Arguments\n", nrArgs);
    printf("File -> %s\n", args[1]);
    printf("Best Lower Bound -> %s\n", args[2]);
}

//Check if file exists. Returns 0 in case it does and 1 in case it doesnt
int checkFileConsistency(FILE *fp)
{
    if (fp == NULL) {
        return 1;
    }
    return 0;
}

int getFileNumberRows(FILE *fp)
{
    int num_rows=0;
        char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            num_rows++;
        }
    }
    return num_rows;
}

//prints the matrix
void printMatrix(int num_rows)
{
    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

//frees the memory space from the matrix
void freeMatrix(int num_rows)
{
    for (int i = 0; i < num_rows; i++) {
            free(matrix[i]);
        }
    free(matrix);
}

//creates the matrix based on of the input file
void createMatrix(FILE *fp, int num_rows)
{
    matrix = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; i++) {
        matrix[i] = (int *)malloc(num_rows * sizeof(int));
    }

    char line[MAX_LINE_LENGTH]; 
    char *token;
    int y = 0;
    fgets(line, MAX_LINE_LENGTH, fp); //reads and discards the first line
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) 
    {
        // printf("%s", line);
        token = strtok(line, " ");
        int x = 0;
        while (token != NULL) {
            // printf(" || TOKEN : %d\n", atoi(token));
            matrix[y][x] = atoi(token);
            token = strtok(NULL, " ");
            x++;
        }
        y++;
    }
}


//reads the citys and distances between them from text file
void getMapData(char *filename)
{
    int num_rows = 0;
    FILE* fp = fopen(filename, "r");
    
    if (checkFileConsistency(fp) == 1) {
        printf("Error: Unable to open file '%s'\n", filename);
        return;
    }
    
    num_rows = getFileNumberRows(fp);
    rewind(fp);

    createMatrix(fp, num_rows);
    
    fclose(fp);

    printMatrix(num_rows);
}

// core function
void tsp(char *filename)
{
    getMapData(filename);
}

//main
int main(int argc, char *argv[])
{
    double exec_time;

    if (argc != 3) {
        printf("Number of arguments is incorrect. Should be 2");
        return 1;
    }
    // argumentSumary(argc, argv);
    
    // exec_time = -omp_get_wtime();

    tsp(argv[1]);

    // exec_time += omp_get_wtime();
    // fprintf(stderr, "%.lfs\n");

    // print_result();

    return 0;
}
