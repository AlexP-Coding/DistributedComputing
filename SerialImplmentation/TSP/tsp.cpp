#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include"./nqueue/queue.hpp"
#include"city.hpp"
#include"tour.hpp"

#define MAX_LINE_LENGTH 10
#define NUM_COLLUMNS 3

#define NA_VALUE -1

int NUMBER_ROWS;
int NUM_CITIES;
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
       else if ( tour_a.getBound() == tour_b.getBound() && tour_a.getCurrCity().getId() > tour_b.getCurrCity().getId() )   
       {
           return true;
       }
       return false;
    }
};

//Check if file exists. Returns 0 in case it does and 1 in case it doesnt
int checkFileConsistency(FILE *fp)
{
    if (fp == NULL) {
        return 1;
    }
    return 0;
}

// Initializes the cities array
void createCities()
{
    cities = new City[NUM_CITIES];
    for (int i = 0 ; i < NUM_CITIES ; i++ )
    {
        cities[i] = *new City(i, NUM_CITIES);
    }
}

// Fills the data of the cities in the cities array
void buildCity(FILE* fp)
{
    fscanf(fp, "%d %d", &NUM_CITIES, &NUMBER_ROWS);
    createCities();

    int city1, city2;
    double edgeCost;

    for (int i = 0; i < NUMBER_ROWS; i++) 
    {
        fscanf(fp, "%d %d %lf", &city1, &city2, &edgeCost);

            // std::cout << "Cities: " << city1 << " <-> " << city2 << std::endl;
            // std::cout << "Cost " << edgeCost << std::endl;

        cities[city1].addNeighbour(city2, edgeCost);
        cities[city2].addNeighbour(city1, edgeCost);
    }
    // std::cout << "All Cities Built!!!" << std::endl;
}

// Retrieves the data from the input file and stores it in the aproppriate variables
void getMapData(char* filename)
{      
    FILE* fp = fopen(filename, "r");
    if ( checkFileConsistency(fp) ) 
    {
        printf("Error: Unable to open file '%s'\n", filename);
        exit(1);
    }
    buildCity(fp);
    fclose(fp);
}

Tour getNewTour(Tour oldTour, City newCity,double roadCost, double newBound)
{
    Tour newTour = Tour(
        oldTour.getCost(),
        newBound,
        newCity
    );

    newTour.setTour(oldTour.getTour());
    newTour.addCity(newCity, roadCost, newBound);
    return newTour;
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
double recomputeLowerBound(double oldLowerBound, double roadCost, City oldCity, City newCity)
{
    return (oldLowerBound + roadCost - ( oldCity.getHigherLowerTruncatedCostEdge(roadCost) + newCity.getHigherLowerTruncatedCostEdge(roadCost)) / 2 );
}


//  Core Function
Tour tsp(char* filename, double maxTourCost)
{
    getMapData(filename);

    double initialLowerBound = computeInitialLowerBound();
    double recomputedLowerBound;

    bestTour = Tour(maxTourCost, NA_VALUE, City(-1,-1));
    PriorityQueue<Tour, cmp_Tours> journey;
    std::cout << "----------------------" << std::endl;
    journey.push(Tour(0, initialLowerBound, cities[0]));
    int s = journey.size();
    

    while ( journey.size() != 0 )
    {
        Tour currTour = journey.pop();

        currTour.toString();

        if ( currTour.getBound() >= bestTour.getCost() )
        {
            bestTour.toString();
            return bestTour;
        }
        if( currTour.getSize() == NUM_CITIES )
        {
            if ( //currTour.connectsToBase() &&
                ( currTour.getCost() + currTour.getRoadCostTo(0) < bestTour.getCost() ))
            {
                double roadCostToZero = currTour.getRoadCostTo(0);
                bestTour.addCity(cities[0], roadCostToZero, recomputeLowerBound(currTour.getBound(), roadCostToZero, currTour.getCurrCity(), cities[0]));
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
                    currTour.getRoadCostTo(unvisitedNeighbours[i]),
                    currTour.getCurrCity(),
                    cities[unvisitedNeighbours[i]]
                );
                if ( recomputedLowerBound > bestTour.getCost() )
                {
                    continue;
                }
                short roadCost = currTour.getCurrCity().getRoadCost(unvisitedNeighbours[i]);
                journey.push(getNewTour(currTour, cities[unvisitedNeighbours[i]], roadCost, recomputedLowerBound));
                std::cout << "??????????????????" << std::endl;
            }
            free(unvisitedNeighbours);
        }
        currTour.~Tour();
    }
    bestTour.toString();
    std::cout << "FIM" << std::endl;
    return bestTour;
}

// main
int main(int argc, char *argv[]) 
{
    tsp(argv[1], atof(argv[2]));
    return 0;
}