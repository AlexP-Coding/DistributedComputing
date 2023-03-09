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
    // std::cout << "old Lower Bound " << oldLowerBound << std::endl;
    // std::cout << "Road Cost " << roadCost << std::endl;
    // std::cout << "old city " << oldCity.getId() << std::endl;
    // std::cout << "new city S" << newCity.getId() << std::endl;
    // std::cout << "---------------------BUG" << std::endl;
    return (oldLowerBound + roadCost - ( oldCity.getHigherLowerTruncatedCostEdge(roadCost) + newCity.getHigherLowerTruncatedCostEdge(roadCost)) / 2 );
}

Tour getNewTour(Tour oldTour, City newCity,double roadCost, double newBound)
{
    Tour newTour;

    newTour.setTour(oldTour.getTour());
    newTour.setSize(oldTour.getSize());
    newTour.setCost(oldTour.getCost());
    newTour.setBound(newBound);


    // std::cout << "Adding " << newCity.getId() << " from " << newTour.getCurrCity().getId() << " ; Cost to add: " << roadCost << std::endl;

    newTour.setCurrCity(newCity);

    
    newTour.addCity(newCity, roadCost, newBound);
    return newTour;
}

//  Core Function
Tour tsp(char* filename, double maxTourCost)
{
    getMapData(filename);

    double initialLowerBound = computeInitialLowerBound();
    double recomputedLowerBound;

    bestTour = Tour(maxTourCost, NA_VALUE, City(-1,-1));
    PriorityQueue<Tour, cmp_Tours> journey;
    // std::cout << "----------------------" << std::endl;
    journey.push(Tour(0, initialLowerBound, cities[0]));



    // for ( int i = 0 ; i < NUM_CITIES ; i++ )
    // {
    //     std::cout << "City : " << i << std::endl;
    //     cities[i].toString();

    // }
    while ( journey.size() > 0 )
    {
        Tour currTour = journey.pop();

        // currTour.toString();

        if ( currTour.getBound() >= bestTour.getCost() )
        {
            std::cout << "Return Best" << std::endl;
            // bestTour.toString();
            return bestTour;
        }
        if( currTour.getSize() == NUM_CITIES )
        {
            if ( currTour.getCurrCity().getConnectsToStart() == 1 &&
                ( currTour.getCost() + currTour.getRoadCostTo(0) < bestTour.getCost() ))
            {
                std::cout << "Best Updated" << std::endl;
                double roadCostToZero = currTour.getRoadCostTo(0);
                bestTour = getNewTour(currTour, cities[0], roadCostToZero, currTour.getBound());
            }
        }
        else
        {
            int unvNeiNumber;
            int* unvisitedNeighbours = currTour.getUnvisitedCities(&unvNeiNumber);
            // std::cout << unvNeiNumber  << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
            for ( int i = 0 ; i < unvNeiNumber ; i++ )
            {
                
                // std::cout << " . " << std::endl;
                
                // for ( int i = 0 ; i < unvNeiNumber ; i++)
                // {
                
                //     std::cout << "------------------------------------------" << std::endl;
                //     std::cout << currTour.getCurrCity().getCosts()[i] << " - ";
                //     std::cout << currTour.getRoadCostTo(unvisitedNeighbours[i]) << " - ";
                //     std::cout << currTour.getCurrCity().getRoadCost(unvisitedNeighbours[i]) << std::endl;
                // }

                recomputedLowerBound = recomputeLowerBound(
                    currTour.getBound(),
                    currTour.getRoadCostTo(cities[unvisitedNeighbours[i]].getId()),
                    currTour.getCurrCity(),
                    cities[unvisitedNeighbours[i]]
                );
                // std::cout << "  -> Recomputed Bound : " << recomputedLowerBound << std::endl;
                if ( recomputedLowerBound > bestTour.getCost() )
                {
                    continue;
                }
                double roadCost = currTour.getRoadCostTo(cities[unvisitedNeighbours[i]].getId());
                journey.push(getNewTour(currTour, cities[unvisitedNeighbours[i]], roadCost, recomputedLowerBound));
            }
            // std::cout << "Free unvisited Neighbours "<< std::endl;
            free(unvisitedNeighbours);
        }
        // TODO: FALTA CONSEGUIR libertar a memoria da tour que vamos deixar de usar!!!!
        // currTour.~Tour();
        // std::cout << "Freed currTour "<< std::endl;
    }

    std::cout << "FIM" << std::endl;
    return bestTour;
}

// main
int main(int argc, char *argv[]) 
{
    Tour result = tsp(argv[1], atof(argv[2]));

    std::cout << result.getCost() << std::endl;
    result.printTour();
    return 0;
}