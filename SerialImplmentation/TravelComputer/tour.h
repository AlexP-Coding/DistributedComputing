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

// Creates and returs a Tour
Tour* createTour(int numCities, int cost, float bound, int currCity, int size);
//compares the travel cost bwtween two cities
char compare_tours(void *a, void *b);

Tour* addCityToTour(Tour* oldtour, short newCity, short roadCost, float newBound,short numCities);
// Prints a tours atributes
void printTour(Tour* tourToPrint);
