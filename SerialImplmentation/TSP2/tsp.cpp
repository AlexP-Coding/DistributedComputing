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
#define NA_VALUE -1

int NUM_ROADS = 0;
int NUM_CITIES = 0;
City* cities;
Tour bestTour;

// Class stores the compare function for the priority queue
class cmp_Tours
{
    public:
    bool operator()(Tour& tour_a, Tour& tour_b) {
       if ( tour_a.getBound() > tour_b.getBound() )
       {
           return true;
       }
       else if ( tour_a.getBound() == tour_b.getBound() && tour_a.getCurrCity()->getId() > tour_b.getCurrCity()->getId() )   
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

    Tour resultTour = tsp(atof(argv[2]));

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1fs\n", exec_time);

    if ( resultTour.getSize() > 2 ){
        std::cout << resultTour.getCost() << std::endl;
        resultTour.printTourPath();
    } else
    {
        std::cout << "NO SOLUTION" << std::endl;
    }
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

Tour tsp(double maxTourCost)
{
    double initialLowerBound = computeInitialLowerBound();
    double recomputedLowerBound;

    std::bitset<128> noVisits;
    bestTour = Tour(maxTourCost, NA_VALUE, City(-1,-1), noVisits);
    PriorityQueue<Tour, cmp_Tours> journey;
    journey.push(Tour(0, initialLowerBound, cities[0], noVisits));

    while ( journey.size() > 0 )
    {
        Tour currTour = journey.pop();

        if ( currTour.getBound() >= bestTour.getCost() )
        {
            return bestTour;
        }
        if( currTour.getSize() == NUM_CITIES )
        {
            if ( currTour.getCurrCity().getConnectsToStart() == 1 &&
                ( currTour.getCost() + currTour.getRoadCostTo(0) < bestTour.getCost() ))
            {
                double roadCostToZero = currTour.getRoadCostTo(0);
                bestTour = getNewTour(currTour, cities[0], roadCostToZero, currTour.getBound());
            }
        }
        else
        {
            int unvNeiNumber;
            int* unvisitedNeighbours = currTour.getUnvisitedCities(&unvNeiNumber);
            for ( int i = 0 ; i < unvNeiNumber ; i++ )
            {
                recomputedLowerBound = recomputeLowerBound(
                    currTour.getBound(),
                    currTour.getRoadCostTo(cities[unvisitedNeighbours[i]].getId()),
                    currTour.getCurrCity(),
                    cities[unvisitedNeighbours[i]]
                );
                if ( recomputedLowerBound > bestTour.getCost() )
                {
                    continue;
                }
                double roadCost = currTour.getRoadCostTo(cities[unvisitedNeighbours[i]].getId());
                journey.push(getNewTour(currTour, cities[unvisitedNeighbours[i]], roadCost, recomputedLowerBound));
            }
            free(unvisitedNeighbours);
        }
        // TODO: FALTA CONSEGUIR libertar a memoria da tour que vamos deixar de usar!!!!
        // currTour.~Tour();
    }
    std::cout << "FIM" << std::endl;
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
    cities = (City*) malloc(sizeof(City)*NUM_CITIES);
    for (int i = 0 ; i < NUM_CITIES ; i++ )
    {
        cities[i] = City(i, NUM_CITIES);
    }
}


// Computes the inicial lower bound
double computeInitialLowerBound()
{
    double lowerBound = 0;
    for ( int i = 0 ; i < NUM_CITIES  ; i++ )
    {
        lowerBound = lowerBound + cities[i].getLowestCostEdgesSum();
    }
    return ( lowerBound / 2);
}

// Recomputes the LowerBound to new Tour
double recomputeLowerBound(double oldLowerBound, double roadCost, City *oldCity, City *newCity)
{  
    return (oldLowerBound + roadCost - ( oldCity->getHigherLowerTruncatedCostEdge(roadCost) + newCity->getHigherLowerTruncatedCostEdge(roadCost)) / 2 );
}

// Returns a new tour based on the Tour given as an arguement and updates its attributes with the other arguments
Tour* getNewTour(Tour *oldTour, City* newCity,double roadCost, double newBound)
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
