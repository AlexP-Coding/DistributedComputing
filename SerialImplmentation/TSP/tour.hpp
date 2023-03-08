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
        Tour(int numCities, double cost, double bound, City currCity)
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

        void addCity(City newCity, double newCost)
        {
            this->addCost(newCost);
            this->tour.push_back(newCity.getId());
            this->setCurrCity(newCity);
            this->increaseSize();
        }

        double getRoadCostTo(int newCity)
        {
            return this->currCity.getRoadCost(newCity);
        }

        void addCost(double newCost)
        {
            this->setCost( this->getCost() + newCost );
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

        int getSize()
        {
            return this->size;
        }

        void setCurrCity(City newCity)
        {
            this->currCity = newCity;
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