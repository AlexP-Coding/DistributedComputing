#include <iostream>
#include <vector>
#include"city.hpp"


#ifndef TOUR_HPP
#define TOUR_HPP
class Tour {
    private:
        std::vector<int> tour;
        unsigned int size;
        double cost;
        double bound;
        City currCity;

    public:
        Tour(){}

        // Constructor of class City
        Tour(double cost, double bound, City currCity)
        {   
            this->tour.push_back(currCity.getId());
            this->bound = bound;
            this->cost = cost;
            this->size = 1;
            this->currCity = currCity;
        }

        // Deconstructor of class City
        ~Tour()
        {
            this->tour.clear();
        }

        // Adds a city to the tour
        void addCity(City newCity, double roadCost, double newBound)
        {
            this->addCost(roadCost);
            this->tour.push_back(newCity.getId());
            this->setCurrCity(newCity);
            this->increaseSize();
            this->setBound(newBound);

        }

        // Returns the neighbours of a city that have not been traversed yet
        int* getUnvisitedCities(int* numUnvisCities)
        {
            int* unvisitedNeighbours = (int*) malloc(sizeof(int) * this->getCurrCity().getNrNeighbours());
            int pos = 0;
            for ( int i = 0 ; i < this->getCurrCity().getNrNeighbours() ; i++ )
            {
                if (!hasBeenTraversed(this->getCurrCity().getNeighbours()[i]))
                {
                    unvisitedNeighbours[pos] = this->getCurrCity().getNeighbours()[i];
                    pos++;
                }
            }
            *numUnvisCities = pos;
            return unvisitedNeighbours;
        }

        // Check if a city has been traversed
        bool hasBeenTraversed(int cityIndex)
        {
            bool did = 0;
            for ( int i = 0 ; i < this->getSize() ; i++ )
            {
                if ( cityIndex == this->getTour()[i] )
                {
                    did = true;
                    break;
                }
            }
            return did;
        }

        double getRoadCostTo(int newCity)
        {
            return this->currCity.getRoadCost(newCity);
        }

        void addCost(double newCost)
        {
            this->setCost( this->getCost() + newCost );
        }

        void setTour(std::vector<int> tour)
        {  
            this->tour = tour;
        }

        std::vector<int> getTour()
        {
            return this->tour;
        }

        void setBound(double newBound)
        {
            this->bound = newBound;
        }

        double getBound()
        {
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

        City getCurrCity()
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

        void setCurrCity(City newCity)
        {
            this->currCity = newCity;
        }

        void printTour()
        {
            for ( int city : this->tour)
            {
                std::cout << city << " ";
            }
            std::cout << std::endl;
        }

        void toString() const
        {
            std::cout << "Tour: ";
            for (auto i : tour) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            std::cout << "Size: " << size << std::endl;
            std::cout << "Cost: " << cost << std::endl;
            std::cout << "Bound: " << bound << std::endl;
            std::cout << "Current City: " << currCity.getId() << std::endl;
        }

};

#endif