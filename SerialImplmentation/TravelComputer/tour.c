#include"tour.h"
#include"arrayManipulation.h"


// Creates and returs a Tour
Tour *createTour(int numCities, int cost, float bound, int currCity, int size)
{
    Tour* tour = malloc(sizeof(Tour));
    tour->tour = (unsigned short*) malloc(sizeof(unsigned short) * (numCities+1));
    tour->size = size;
    tour->cost = cost;
    tour->bound = bound;
    tour->currCity = currCity;

    tour->tour =  add_element(tour->tour, size, currCity);
    tour->size = size+1;

    return tour;
}

 DAD *createDAD(short size)
{
    DAD* d = malloc(sizeof(DAD));
    d->size = size;
    return d;
}

//compares the travel cost bwtween two cities
char compare_tours(void *a, void *b) 
{
    Tour* tour_a = (Tour*)a;
    Tour* tour_b = (Tour*)b;

    if (tour_a->bound > tour_b->bound) {
        return 1;
    }
        return 0;
}

//compares the travel cost bwtween two cities
char compare_DAD(void *a, void *b) 
{
    DAD* dad_a = (DAD*)a;
    DAD* dad_b = (DAD*)b;

    if (dad_a->size > dad_b->size) {
        return 1;
    }

    return 0;
}

// Prints a tours atributes
void printTour(Tour* tourToPrint)
{
    printf("--------------------------------------\n");
    printf("Size - %d\n", tourToPrint->size);
    printf("Tour: ");
    for ( int i = 0 ; i < tourToPrint->size ; i++ )
    {
        printf( "%d ", tourToPrint->tour[i] );
    }
    // printf( "%d ", tourToPrint->tour[2] );
    printf("\n");
    printf("Cost - %d\n", tourToPrint->cost);
    printf("Bound - %f\n", tourToPrint->bound);
    printf("Curr City - %d\n", tourToPrint->currCity);
}