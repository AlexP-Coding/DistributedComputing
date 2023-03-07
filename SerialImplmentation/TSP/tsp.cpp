// Your First C++ Program

#include <iostream>
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

void buildCity(FILE* fp)
{
    cities = new City[NUM_CITIES];

    char line[MAX_LINE_LENGTH]; 
    int cityId1, cityId2;
    double roadCost;

    for ( int cityIndex = 0 ; cityIndex < NUM_CITIES ; cityIndex++ )
    {
        
        std::cout << "aaaa " << cityIndex << std::endl;
        cities[cityIndex] = City (cityIndex, NUM_CITIES);

        for (int i = 0; i < NUMBER_ROWS; i++) 
        {
            std::cout << "ZAZA : " << roadCost << std::endl;
            fscanf(fp, "%d %d %lf", &cityId1, &cityId2, &roadCost);
            
            // std::cout << "City 1 " << cityId1 << std::endl;
            // std::cout << "City 2 " << cityId2 << std::endl;
            // std::cout << "Road Cost " << roadCost << std::endl;

            // std::cout << "v2 -> " << cities[cityIndex].getId() << std::endl;

            if ( cityId1 == cityIndex )
            {
                // std::cout << "PRIM : " << roadCost << std::endl;
                cities[cityIndex].addNeighbour(cityId2, roadCost);
            }
            if ( cityId2 == cityIndex )
            {
                // std::cout << "SEC : " << roadCost << std::endl;
                cities[cityIndex].addNeighbour(cityId1, roadCost);
            }
            std::cout << "TATA : " << roadCost << std::endl;
        }


        cities[cityIndex].toString();
    }

    std::cout << "v3 -> " << std::endl;
    cities[0].toString();
}

void getMapData(char* filename)
{
    FILE* fp = fopen(filename, "r");

    if (checkFileConsistency(fp) == 1) {
        printf("Error: Unable to open file '%s'\n", filename);
        return;
    }

    fscanf(fp, "%d %d", &NUM_CITIES, &NUMBER_ROWS);


    buildCity(fp);
    fclose(fp);
}

//  Core Function
int tsp(char* filename, double maxTourCost)
{
    getMapData(filename);
    
}


// main
int main(int argc, char *argv[])
{

 tsp(argv[1], atof(argv[2]));

 return 0;
}