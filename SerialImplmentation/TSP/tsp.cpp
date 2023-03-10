#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
// #include <omp.h>
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

        cities[city1].addNeighbour(city2, edgeCost);
        cities[city2].addNeighbour(city1, edgeCost);
    }
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

// Returns a new tour based on the Tour given as an arguement and updates its attributes with the other arguments
Tour getNewTour(Tour oldTour, City newCity,double roadCost, double newBound)
{
    Tour newTour;

    newTour.setTour(oldTour.getTour());
    newTour.setSize(oldTour.getSize());
    newTour.setCost(oldTour.getCost());
    newTour.setBound(newBound);
    
    newTour.setCurrCity(newCity);
    newTour.addCity(newCity, roadCost, newBound);
    return newTour;
}

//  Core Function
Tour tsp(double maxTourCost)
{
    double initialLowerBound = computeInitialLowerBound();
    double recomputedLowerBound;

    bestTour = Tour(maxTourCost, NA_VALUE, City(-1,-1));
    PriorityQueue<Tour, cmp_Tours> journey;
    journey.push(Tour(0, initialLowerBound, cities[0]));

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

// main
int main(int argc, char *argv[]) 
{
    double exec_time;

    getMapData(argv[1]);

    // exec_time = -omp_get_wtime();

    Tour resultTour = tsp(atof(argv[2]));

    // exec_time += omp_get_wtime();
    // fprintf(stderr, "%.1fs\n", exec_time);

    if ( resultTour.getSize() > 2 ){
        std::cout << resultTour.getCost() << std::endl;
        resultTour.printTour();
    }else
    {
        std::cout << "NO SOLUTION" << std::endl;
    }
    exit(0);
}