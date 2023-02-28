#include <stdio.h>


// Defines the cost between two cities
typedef struct
{
	unsigned short *tour;
	unsigned short cost;
    unsigned short bound;
    unsigned short currCity;
} Tour;


//compares the travel cost bwtween two cities
char compare_elements(void *a, void *b);