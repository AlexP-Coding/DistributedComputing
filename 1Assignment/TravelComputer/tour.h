#include <stdio.h>
#include <stdlib.h>


// Defines the cost between two cities
typedef struct
{
	unsigned short *tour;
    unsigned short size;
	unsigned short cost;
    unsigned short bound;
    unsigned short currCity;
} Tour;

// Creates and returs a Tour
Tour* createTour(int numCities, int cost, int bound, int currCity);

//compares the travel cost bwtween two cities
char compare_elements(void *a, void *b);