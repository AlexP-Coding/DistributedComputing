#include"queue.h"
#include"tour.h"
#include"arrayManipulation.h"
// #include<omp.h>

#define MAX_LINE_LENGTH 10
#define NUM_COLLUMNS 3
int NUM_ROWS;
int NUM_CITIES;

int **matrix;
double bestLowerBound;

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

// Returns the Road Cost between two Cities
short getRoadCost(short oldCityIndex, short newCityIndex)
{
    short cost;
    for ( short i = 0 ; i < NUM_ROWS ; i++ )
    {
        if ( matrix[i][0] == oldCityIndex && matrix[i][1] == newCityIndex )
        {
            cost = matrix[i][2];
        }
        if ( matrix[i][0] == newCityIndex && matrix[i][1] == oldCityIndex )
        {
            cost = matrix[i][2];
        }
    }
    return cost;
}

// Returns the highest cost edge from a city
int getHighestCostEdge(short cityIndex)
{
    int max = 0;
    for ( int i = 0 ; i < NUM_ROWS ; i++ )
    {
        if ( matrix[i][0] == cityIndex || matrix[i][1] == cityIndex )
        {
            if ( matrix[i][2] > max )
            {
                max = matrix[i][2];
            }
        }
    }
    return max;
}

// Creates the matrix based on of the input file
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

// Returns the neighbours of a city
short* getNeighbours(int index) {
    short* neighbours = malloc(sizeof(int) * NUM_CITIES-1);
    int count = 0;

    // Fills the array with -1
    for (int i = 0; i < NUM_CITIES; i++) { neighbours[i] = -1;}

    // Loop through each row in the matrix
    for (int i = 0; i < NUM_ROWS; i++) {
        // If the first element matches the index, add the second element to matches
        if (matrix[i][0] == index) {
            neighbours[count] = matrix[i][1];
            count++;
        }
        // If the second element matches the index, add the first element to matches
        else if (matrix[i][1] == index) {
            neighbours[count] = matrix[i][0];
            count++;
        }
    }

    return neighbours;
}

// Returns whether or not a city has been traversed or not based on the argument traversedCities
short hasBeenTraversed(short cityIndex, short *traversedCities, short pathSize)
{
    int result = 0;
    for ( short i = 0 ; i < pathSize ; i++ )
    {
        if ( cityIndex == traversedCities[i] )
        {
            result = 1;
            break;
        }
    }
    return result;
}

// Returns the neighbours of a city that have not been traversed yet
short* getUnvisitedNeighbourNodes(short cityIndex, short *traversedCities, short pathSize)
{
    short remainingNumberOfNeighbours = NUM_CITIES - pathSize;
    short *unvisitedNeighbours = (unsigned short*) malloc(sizeof(unsigned short) * remainingNumberOfNeighbours);
    short *neighbours = getNeighbours(cityIndex);
    short pos=0;

    for ( short i = 0; i < NUM_CITIES-1 ; i++)
    {
        if ( neighbours[i] != -1 && hasBeenTraversed(neighbours[i], traversedCities, pathSize) == 0)
        {
            unvisitedNeighbours[pos] = neighbours[i];
            pos++;
        }
    }
    return unvisitedNeighbours;
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

    //printMatrix();
}



// Gets the sum of the two smallest edges for each city
int getMinCostSum(short cityIndex)
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

// Computes and returns the initial lower bound
double computeInitialLowerBound()
{
    int lowerBound = 0;
    for ( int i = 0 ; i < NUM_CITIES ; i++ )
    {
        lowerBound = lowerBound + getMinCostSum(i);
    }
    bestLowerBound = lowerBound;
    return (lowerBound / 2) ;
}

// Identifies and returns the lowest highest edge, if its lower than the argument 'truncateValue'
int getHighestTruncatedEdge(int truncateValue, short cityIndex)
{
    int edge = -1;
    for ( int i = 0 ; i < NUM_ROWS ; i++ )
    {
        if ( matrix[i][0] == cityIndex || matrix[i][1] == cityIndex )
        {
            if ( matrix[i][2] > edge && matrix[i][2] <= truncateValue && matrix[i][2] != getHighestCostEdge(cityIndex))
            {
                edge = matrix[i][2];
            }
        }
    }
    return edge;
}

// Recomputes the LowerBound to new Tour
double recomputeLowerBound(double oldLowerBound, int roadCost, short oldCityIndex, short newCityIndex)
{
    return ( oldLowerBound + roadCost - (getHighestTruncatedEdge(roadCost, oldCityIndex) + getHighestTruncatedEdge(roadCost, newCityIndex)) / 2); 
}

// core function
Tour tsp(char *filename, int maxLowerBound)
{
    getMapData(filename);


    int lowerBound = computeInitialLowerBound();
    printf("Initial Lower Bound -> %d", lowerBound);
    if ( lowerBound > maxLowerBound ) { return NULL ; }
    
    short bestTourCost = maxLowerBound;

    priority_queue_t* cities = queue_create(compare_elements);
    
    Tour* currTour = createTour(NUM_CITIES, 0, bestLowerBound, 0);

    queue_push(cities, currTour);
    while ( cities->size > 0 )
    {
        currTour = queue_pop(cities);

        //  if (Bound > BestTourCost)
        //      return BestTour, BestTourCost

         if (currTour->size == NUM_CITIES) {
            //
            if ( ( currTour->cost + getRoadCost(currTour->currCity,0) ) < bestTourCost ){
                BestTour = BestTour.append(0)           
                BestTourCost = Cost + Distances(Node, 0)
            }
        }
        else {
            short *unvisitedNeighbours = getUnvisitedNeighbourNodes(currTour->currCity, currTour->tour, currTour->size);
            for ( short i = 0 ; i < (NUM_CITIES - currTour->size) ; i++ ){
                currTour->bound = recomputeLowerBound(currTour->bound, getRoadCost(currTour->currCity, unvisitedNeighbours[i]), currTour->currCity, unvisitedNeighbours[i]);
                if ( currTour->bound > bestTourCost )
                {
                    continue;
                }
                //  newCost = cost + Distances(Nodes,v)
                currTour->cost = currTour->cost + getRoadCost(currTour->currCity, unvisitedNeighbours[i]);
                //  newTour = newTour + new visited City
                currTour->tour = add_element(currTour->tour, currTour->size+1, unvisitedNeighbours[i]);
                currTour->size=currTour->size+1;
                currTour->currCity = unvisitedNeighbours[i];
                //  Queue.add( new visited city)
                queue_push(cities, currTour);
            }
        }
    }
    // free(currCity);
    //  return BestTour, BetterTourCost
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

    Tour result = tsp(argv[1], atoi(argv[2]));

    if ( &result == NULL )
    {
        printf("NO SOLUTION");
    }
    else
    {

    }
    // exec_time += omp_get_wtime();
    // fprintf(stderr, "%.lfs\n");

    // print_result();

    return 0;
}