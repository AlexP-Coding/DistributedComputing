#include"queue.h"

#define MAX_LINE_LENGTH 10

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

//reads the citys and distances between them from text file
void getMapData(char *filename)
{
    FILE* fp = fopen(filename, "r");
    
    if (checkFileConsistency(fp) == 1) {
        printf("Error: Unable to open file '%s'\n", filename);
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
}

// core function
void tsp(char *filename)
{
    getMapData(filename);
}

//main
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Number of arguments is incorrect. Should be 2");
        return 1;
    }
    argumentSumary(argc, argv);

    tsp(argv[1]);

    return 0;
}