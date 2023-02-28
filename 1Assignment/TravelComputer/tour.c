#include"tour.h"


//compares the travel cost bwtween two cities
char compare_elements(void *a, void *b) {
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