#include <iostream>
#include "city.hpp"
#include "tour.hpp"

void createCities();
void buildMap(FILE* fp);
void getMapData(char* filename);
double computeInitialLowerBound();
double recomputeLowerBound(double oldLowerBound, double roadCost, City oldCity, City newCity);
Tour* getNewTour(Tour oldTour, City newCity,double roadCost, double newBound);
Tour tsp(double maxTourCost);