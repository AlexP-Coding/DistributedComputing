#include"queue.h"
#include<omp.h>

#define MAX_LINE_LENGTH 10
#define NUM_COLLUMNS 3
int NUM_ROWS;
int NUM_CITIES;

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

//gets the number of lines from a file
void getFileNumberRows(FILE *fp)
{
    int num_rows=0;
        char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            num_rows++;
        }
    }
    NUM_ROWS = num_rows;
}

//prints the matrix
void printMatrix()
{
    printf("\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLLUMNS; j++) {
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
void createMatrix(FILE *fp)
{
    /* Allocates memory for the matrix */
    matrix = (int **)malloc(NUM_ROWS * sizeof(int *));
    for (int i = 0; i < NUM_ROWS; i++) {
        matrix[i] = (int *)malloc(NUM_ROWS * sizeof(int));
    }

    char line[MAX_LINE_LENGTH]; 
    char *token;
    int y = 0;

    /* Gets the number of cities and number of roads*/
    fgets(line, MAX_LINE_LENGTH, fp); 
    NUM_CITIES = atoi(strtok(line, " "));
    
    /* Fills the matrix */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) 
    {
        // printf("%s", line);
        token = strtok(line, " ");
        int x = 0;
        while (token != NULL) {
            // printf("`TOKEN : %d\n", atoi(token));
            matrix[y][x] = atoi(token);
            token = strtok(NULL, " ");
            x++;
        }
        y++;
    }
}


//reads the cities and distances between them from text file
void getMapData(char *filename)
{
    FILE* fp = fopen(filename, "r");
    
    if (checkFileConsistency(fp) == 1) {
        printf("Error: Unable to open file '%s'\n", filename);
        return;
    }
    
    getFileNumberRows(fp);
    rewind(fp);

    createMatrix(fp);
    
    fclose(fp);

    printMatrix();
}

int* remove_element(int* arr, int size, int pos) {
    // Check if pos is within bounds
    if (pos < 0 || pos >= size) {
        return arr; // Return the original array if pos is invalid
    }

    // Allocate memory for the new array
    int* new_arr = (int*) malloc((size - 1) * sizeof(int));

    // Copy the elements from arr to new_arr, except for the one at pos
    int j = 0; // Index for the new array
    for (int i = 0; i < size; i++) {
        if (i != pos) {
            new_arr[j] = arr[i];
            j++;
        }
    }

    // Free the memory used by the original array
    free(arr);

    // Return the new array
    return new_arr;
}

int* add_element(int* arr, int size, int element) {
    // Allocate memory for the new array
    int* new_arr = (int*) malloc((size + 1) * sizeof(int));

    // Copy the elements from arr to new_arr
    for (int i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }

    // Add the new element to the end of the new array
    new_arr[size] = element;

    // Free the memory used by the original array
    free(arr);

    // Return the new array
    return new_arr;
}


int getMinCostSum(int cityIndex)
{
    int min1 = 1000000000;
    int min2 = 1000000000;

    int *arr = NULL;
    int arr_size=0;

    /* creates an array with all the cost associated to the argumnent cityIndex*/
    for ( int i = 0 ; i < NUM_ROWS ; i++ )
    {
        // printf("BBBBBB %d : %d ||| ", matrix[i][0],  matrix[i][1]);
        if ( matrix[i][0] == cityIndex || matrix[i][1] == cityIndex )
        {
            // printf("CCCCCCCCC %d : %d ||| ", matrix[i][0],  matrix[i][1]);
            int cost = matrix[i][2];   
            
            arr = add_element(arr, arr_size, cost);
            arr_size++;
        }
    }

    /*  gets both the smallest member in the array and its position*/
    min1 = arr[0];
    int pos = 0;
    for (int i = 1; i <  arr_size ; i++)
    {
        if ( arr[i] < min1 )
        {
            min1 = arr[i];
            pos=i;
        }
    }
    arr = remove_element(arr, arr_size, pos);
    arr_size = arr_size - 1;
    
    /* repeat the abovce*/
    min2 = arr[0];
    for (int i = 0; i <  arr_size ; i++)
    {
        if ( arr[i] < min2 )
        {
            min2 = arr[i];
            pos = i;
        }
    }
    arr = remove_element(arr, arr_size, pos);
    arr_size = arr_size - 1;

    // printf("AAAA %d -- %d\n", min1, min2);

    free(arr);
    return ( min1 + min2 );
}

double computeLowerBound()
{
    for ( int i = 0 ; i < NUM_CITIES ; i++ )
    {
        printf("City %d -> %d\n", i, getMinCostSum(i));
    }

    return 0.0;
}

// core function
void tsp(char *filename)
{
    getMapData(filename);
    computeLowerBound();
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
