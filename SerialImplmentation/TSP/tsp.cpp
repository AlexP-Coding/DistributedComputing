// Your First C++ Program

#include <iostream>
#include <cstring>
#include <string>
#include"./nqueue/queue.hpp"
#include"city.hpp"
#include"tour.hpp"

#define MAX_LINE_LENGTH 10
#define NUM_COLLUMNS 3
int NUMBER_ROWS;
int NUM_CITIES;

#define NA_VALUE -1

City* cities;
Tour bestTour;


struct cmp_Tours
{
     bool compareTours(Tour tour_a, Tour tour_b) {
        if ( tour_a.getBound() > tour_b.getBound() )
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
        cities[i] = City(i, NUM_CITIES);
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

    if (checkFileConsistency(fp) == 1) 
    {
        printf("Error: Unable to open file '%s'\n", filename);
        return;
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

//  Core Function
Tour tsp(char* filename, double maxTourCost)
{
    getMapData(filename);
    // for ( int i = 0 ; i < NUM_CITIES ; i++ )
    // {
    //     cities[i].toString();
    // }

    double initialLowerBound = computeInitialLowerBound();
    double recomputedLowerBound;

    bestTour = Tour( NA_VALUE, maxTourCost, NA_VALUE, City(-1,-1));

    bestTour.toString();

    PriorityQueue<Tour, cmp_Tours> travel = PriorityQueue<Tour, cmp_Tours>();
    // travel.push(Tour(NUM_CITIES, 0, initialLowerBound, 0));

    // Tour t = travel.pop();
    // t.toString();
    while ( travel.size() != 0 )
    {
        
        Tour currTour = travel.pop();


        if ( currTour.getBound() >= bestTour.getCost() )
        {
            return bestTour;
        }
        if( currTour.getSize() == NUM_CITIES )
        {
            if ( //currTour.connectsToBase() &&
                ( currTour.getCost() + currTour.getRoadCostTo(0) < bestTour.getCost() ))
            {
                bestTour.addCity(City(0, NA_VALUE), currTour.getRoadCostTo(0));
            }
        }
        else
        {
            // get Unvisited Neighbours

        }
        
        // delete &currTour;
        currTour.~Tour();

    }

    std::cout << "FIM" << std::endl;
    return bestTour;
}


// main
int main(int argc, char *argv[]) 
{
    tsp(argv[1], atof(argv[2]));
    return 0;
}