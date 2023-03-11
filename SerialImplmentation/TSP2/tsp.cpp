#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "./nqueue/queue.hpp"
#include "city.hpp"
#include "tour.hpp"
#include "tsp.hpp"

#define NA_VALUE -1

int NUM_ROADS = 0;
int NUM_CITIES = 0;
City* cities;
Tour* bestTour;

// Class stores the compare function for the priority queue
class cmp_Tours
{
    public:
    bool operator()(Tour* tour_a, Tour* tour_b) {
       if ( tour_a->getBound() > tour_b->getBound() )
       {
           return true;
       }
       else if ( tour_a->getBound() == tour_b->getBound() && tour_a->getCurrCity()->getId() > tour_b->getCurrCity()->getId() )   
       {
           return true;
       }
       return false;
    }
};


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Received %d arguments instead of 3.\n", argc);
        exit(1);
    }

    double exec_time;

    getMapData(argv[1]);

    exec_time = -omp_get_wtime();

    Tour* resultTour = tsp(atof(argv[2]));

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1fs\n", exec_time);


    if ( resultTour->getSize() > 2 ){
        std::cout << resultTour->getCost() << std::endl;
        resultTour->printTourPath();
    } else
    {
        std::cout << "NO SOLUTION" << std::endl;
    }

    freeCities();

    exit(0);
}

// Retrieves the data from the input file and stores it in the aproppriate variables
void getMapData(char* filename)
{      
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file '%s'\n", filename);
        exit(1);
    }
    buildMap(fp);
    fclose(fp);
}


Tour* tsp(double maxTourCost)
{
    double initialLowerBound = computeInitialLowerBound();
    double recomputedLowerBound;
    double bestTourCost;

    std::bitset<128> citiesVisited;

    Tour *bestTour = (Tour*) malloc(sizeof(Tour));
    bestTour->setTour(0, DBL_MAX, &cities[0], citiesVisited);

    citiesVisited[0] = true;
    Tour* tour = (Tour*) malloc(sizeof(Tour));
    tour->setTour(0, initialLowerBound, &cities[0], citiesVisited);

    PriorityQueue<Tour*, cmp_Tours> journey;
    journey.push(tour);

    while (!journey.empty())
    {
        Tour* tourNode = journey.pop();

        if (tourNode->getBound() >= bestTour->getCost()) {
            return bestTour;
        }

        if (bestTour->getSize() == NUM_CITIES) {
            double distToZero = bestTour->getCurrCity()->getEdgeCost(0);
            double fullCost = bestTour->getCost() + distToZero;

            if (distToZero > 0 && fullCost < bestTourCost) {
                Tour* newBestTour = (Tour*) malloc(sizeof(Tour));
                newBestTour->setTour(0, initialLowerBound, &cities[0], citiesVisited);
                newBestTour->addCity(&cities[0], distToZero, tourNode->getBound());
                Tour *oldBestTour = bestTour;
                bestTour = newBestTour;
                free(oldBestTour);
            }
        }
        else {
            int nrUnvisitedNeighbours;
            int *unvisitedNeighbours = tourNode->getUnvisitedCities(&nrUnvisitedNeighbours);

            for (int i = 0; i < nrUnvisitedNeighbours; i++) {
                recomputedLowerBound = recomputeLowerBound(
                    recomputedLowerBound,
                    tourNode->getRoadCostTo(unvisitedNeighbours[i]),
                    tourNode->getCurrCity(), 
                    &cities[unvisitedNeighbours[i]]
                );

                if (recomputedLowerBound > bestTour->getCost()) {
                    continue;
                }
                
                double newCost = tourNode->getCost() + tourNode->getRoadCostTo(i);
                Tour *newTour = tourNode->getNextTourNode(&cities[unvisitedNeighbours[i]], newCost, recomputedLowerBound);
                journey.push(newTour);
            }
        }
    }
    return bestTour;
}


void buildMap(FILE *fp) {
    int valuesRead;

    valuesRead = fscanf(fp, "%d %d", &NUM_CITIES, &NUM_ROADS);
    if (valuesRead != 2) {
        printf("Error: Read %d values instead of 2.\n", valuesRead);
        fclose(fp);
        exit(1);
    }

    initCities();

    int city1, city2;
    double edgeCost;

    for (int i = 0; i < NUM_ROADS; i++) 
    {
        valuesRead = fscanf(fp, "%d %d %lf", &city1, &city2, &edgeCost);
        if (valuesRead != 3) {
            printf("Error: Read %d values instead of 3.\n", valuesRead);
            fclose(fp);
            exit(1);
        }

        cities[city1].addNeighbour(city2, edgeCost);
        cities[city2].addNeighbour(city1, edgeCost);
    }
}

void initCities() {
    cities = new City[NUM_CITIES];
    for (int i = 0 ; i < NUM_CITIES ; i++ )
    {
        cities[i].setCity(i, NUM_CITIES);
    }
}

void freeCities() {
    for (int i = NUM_CITIES-1; i >= 0; i--) {
        cities[i].~City();
    }
    free(cities);
}


// Computes the inicial lower bound
double computeInitialLowerBound()
{
    double lowerBound = 0;
    for ( int i = 0 ; i < NUM_CITIES  ; i++ )
    {
        lowerBound += cities[i].getLowestCostEdgesSum();
    }
    return ( (double) lowerBound / 2);
}

// Recomputes the LowerBound to new Tour
double recomputeLowerBound(double oldLowerBound, double roadCost, City* oldCity, City* newCity)
{  
    double cf = oldCity->getHigherLowerTruncatedCostEdge(roadCost);
    double ct = newCity->getHigherLowerTruncatedCostEdge(roadCost);
    double res = oldLowerBound + roadCost - ( cf + ct ) / 2;
    return res;
}

// Returns a new tour based on the Tour given as an arguement and updates its attributes with the other arguments
Tour* getNewTour(Tour* oldTour, City* newCity, double roadCost, double newBound)
{
    Tour* newTour = (Tour*) malloc(sizeof(Tour));

    newTour->setTourPath(oldTour->getTourPath());
    newTour->setSize(oldTour->getSize());
    newTour->setCost(oldTour->getCost());
    newTour->setBound(newBound);
    
    newTour->setCurrCity(newCity);
    newTour->addCity(newCity, roadCost, newBound);
    return newTour;
}
