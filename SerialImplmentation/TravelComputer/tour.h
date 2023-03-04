#include <stdio.h>
#include <stdlib.h>


// Defines the cost between two cities
typedef struct
{
	unsigned short *tour;
    unsigned short size;
	unsigned short cost;
    float bound;
    unsigned short currCity;
} Tour;

typedef struct
{
    unsigned short size;   
} DAD;


// Creates and returs a Tour
Tour* createTour(int numCities, int cost, float bound, int currCity, int size);
DAD *createDAD(short size);
//compares the travel cost bwtween two cities
char compare_tours(void *a, void *b);
char compare_DAD(void *a, void *b);

// Prints a tours atributes
void printTour(Tour* tourToPrint);