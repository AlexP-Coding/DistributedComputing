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

    char line[MAX_LINE_LENGTH]; 
    char* token;

    int city1, city2;
    double edgeCost;

    createCities();

    // for ( int cityIndex = 0 ; cityIndex < NUM_CITIES ; cityIndex++ )
    // {
        
        // std::cout << "aaaa " << cityIndex << std::endl;

        fgets(line, MAX_LINE_LENGTH, fp);

        for (int i = 0; i < NUMBER_ROWS; i++) 
        {
            // fscanf(fp, "%d %d %lf", &cityId1, &cityId2, &roadCost);
            fgets(line, MAX_LINE_LENGTH, fp);

            // token = strtok(line, " ");


            fscanf(fp, "%d %d %lf", &city1, &city2, &edgeCost);

            // city1 = atoi(strtok(line, " "));
            // city2 = atoi(strtok(NULL, " "));
            // edgeCost = strtof(strtok(NULL, " "), &token);
            
            // edgeCost = std::strtod(strtok(NULL, " "), nullptr);

            std::cout << "City 1 - " << city1 << std::endl;
            std::cout << "City 2 - " << city2 << std::endl;
            std::cout << "Cost " << edgeCost << std::endl;

            cities[city1].addNeighbour(city2, edgeCost);
            cities[city2].addNeighbour(city1, edgeCost);
            



            // if ( cityId1 == cityIndex )
            // {
            //     // std::cout << "PRIM : " << roadCost << std::endl;
            //     cities[cityIndex].addNeighbour(cityId2, roadCost);
            // }
            // if ( cityId2 == cityIndex )
            // {
            //     // std::cout << "SEC : " << roadCost << std::endl;
            //     cities[cityIndex].addNeighbour(cityId1, roadCost);
            // }
            // std::cout << "TATA : " << roadCost << std::endl;
        }
        std::cout << "AAAAAAAAAAA" << std::endl;

        for ( int i = 0 ; i < NUM_CITIES ; i++ )
        {
            cities[i].toString();
        }
        // std::cout << cities[0].getNeighbours()[0] << std::endl ;

            // cities[cityIndex].toString();
    // }

    std::cout << "v3 -> " << std::endl;
    // cities[0].toString();
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