#include <iostream>
#include <vector>
#include <bitset>
#include"city.hpp"

#ifndef TOUR_HPP
#define TOUR_HPP

class Tour {
    private:
        std::vector<int> tourPath;
        int size;
        double cost;
        double bound;
        City *currCity;
        std::bitset<128> citiesVisited;

    public:
        Tour() {}

        Tour(double cost, double bound, City *currCity, std::bitset<128>& citiesVisited) {
            this->tourPath.push_back(currCity->getId());
            this->bound = bound;
            this->cost = cost;
            this->size = 1;
            this->currCity = currCity;
            this->citiesVisited = citiesVisited;
        }

        ~Tour() {
            this->tourPath.clear();
            std::vector<int> tempVectorInt;
            this->tourPath.swap(tempVectorInt);
        };

        // Adds a city to this tourPath node
        void addCity(City *newCity, double roadCost, double newBound) {
            this->addCost(roadCost);
            this->tourPath.push_back(newCity->getId());
            this->setCurrCity(newCity);
            this->incrementTourSize();
            this->setBound(newBound);
           // ? this->visitCity(newCity->getId());
        }

        // Returns the neighbours of a city that have not been traversed yet
        // and changes the value pointed by the 'numUnvisCities' by the number of neighbours
        int* getUnvisitedCities(int* numUnvisCities)
        {
            int* unvisitedNeighbours = (int*) malloc(sizeof(int) * this->getCurrCity()->getNrNeighbours());
            int pos = 0;
            for ( int i = 0 ; i < this->getCurrCity()->getNrNeighbours() ; i++ )
            {
                if (!hasBeenTraversed(this->getCurrCity()->getNeighbours()[i]))
                {
                    unvisitedNeighbours[pos] = this->getCurrCity()->getNeighbours()[i];
                    pos++;
                }
            }
            *numUnvisCities = pos;
            return unvisitedNeighbours;
        }

        bool hasBeenTraversed(int cityId) {
            return citiesVisited[cityId];
        }

        double getRoadCostTo(int newCity) {
            return this->currCity->getEdgeCost(newCity);
        }

        void addCost(double newCost) {
            this->setCost(this->getCost() + newCost);
        } 


        // Getters and Setters

        void setTourPath(std::vector<int> tourPath) {
            this->tourPath = tourPath;
        }

        void setCitiesVisited(long int citiesVisited) {
            this->citiesVisited = citiesVisited;
        }

        std::vector<int> getTourPath() {
            return this->tourPath;
        }

        void setBound(double newBound) {
            this->bound = newBound;
        }

        double getBound() {
            return this->bound;
        }

        void setCost(double newCost)
        {
            this->cost = newCost;
        }
        double getCost()
        {
            return this->cost;
        }

        City* getCurrCity()
        {
            return this->currCity;
        }

        void increaseSize()
        {
            this->size++;
        }

        void setSize(int newSize)
        {
            this->size = newSize;
        }

        int getSize()
        {
            return this->size;
        }

        void setCurrCity(City *newCity)
        {
            this->currCity = newCity;
        }


        /* Printers */

        void printTourPath()
        {
            for ( int city : this->tourPath)
            {
                std::cout << city << " ";
            }
            std::cout << std::endl;
        }

        void toString() const
        {
            std::cout << "Tour Path: ";
            for (auto i : tourPath) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            std::cout << "Size: " << size << std::endl;
            std::cout << "Cost: " << cost << std::endl;
            std::cout << "Bound: " << bound << std::endl;
            std::cout << "Current City: " << currCity->getId() << std::endl;
        }

        void incrementTourSize() {
            this->size++;
        }



};

#endif