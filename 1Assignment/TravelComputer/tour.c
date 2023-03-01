#include"tour.h"


// Creates and returs a Tour
Tour createTour(int numCities, int cost, int lowerBound, int currCity)
{
    Tour tour;
    tour.tour = (unsigned short*) malloc(sizeof(unsigned short) * numCities);
    tour.cost = cost;
    tour.bound = lowerBound;
    tour.currCity = currCity;
    
    return tour;
}

//compares the travel cost bwtween two cities
char compare_elements(void *a, void *b) 
{
    Tour* tour_a = (Tour*)a;
    Tour* tour_b = (Tour*)b;

    if (tour_a->bound < tour_b->bound) {
        return -1;
    } else if (tour_a->bound > tour_b->bound) {
        return 1;
    } else {
        return 0;
    }
}