// Your First C++ Program

#include <iostream>
#include <cstring>
#include <string>
#include"./nqueue/queue.hpp"
#include"city.hpp"

#define MAX_LINE_LENGTH 10
#define NUM_COLLUMNS 3
int NUMBER_ROWS;
int NUM_CITIES;

City* cities;

//Check if file exists. Returns 0 in case it does and 1 in case it doesnt
int checkFileConsistency(FILE *fp)
{
    if (fp == NULL) {
        return 1;
    }
    return 0;
}

void createCities()
{
    cities = new City[NUM_CITIES];
    for (int i = 0 ; i < NUM_CITIES ; i++ )
    {
        cities[i] = City(i, NUM_CITIES);
    }
}

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
int tsp(char* filename, double maxTourCost)
{
    getMapData(filename);
    // for ( int i = 0 ; i < NUM_CITIES ; i++ )
    // {
    //     cities[i].toString();
    // }

    double initialLowerBound = computeInitialLowerBound();

    std::cout << initialLowerBound << "------------\n";

    return 0;
}


// main
int main(int argc, char *argv[]) 
{
    tsp(argv[1], atof(argv[2]));
    return 0;
}