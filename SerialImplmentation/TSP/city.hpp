#include <iostream>
#include <vector>

//TODO: verificar vizinhos atraves de custos para poupar acessos a memoria
//TODO: verificar se quando os arrays sao formados, ao ler do ficheiro, as cidades ja estao por ordem

#ifndef CITY_HPP
#define CITY_HPP

class City {
    private:
        int nrNeighbours;
        int id;
        int maxNeighbours;
        std::vector<int> neighbours;
        std::vector<double> costs;
        double* lowestCostEdges;
        int connectsToStart;

    public:
        City(){}

        // Constructor of class City
        City(int city_id, int numCities)
        {
            id = city_id;
            maxNeighbours = numCities-1;
            lowestCostEdges = new double[2];
            lowestCostEdges[0] = 1000000.0;
            lowestCostEdges[1] = 1000000.0;
            nrNeighbours=0;
            connectsToStart = 0;
        }

        // Deconstructor of class City
        ~City()
        {
            neighbours.clear();
            costs.clear();
        }


        // Adds a neighbour to the 'neighbours' array and a cost at the same position on to the 'costs' array
        void addNeighbour(int neighbourId, double edgeCost)
        {
            neighbours.push_back(neighbourId);
            costs.push_back(edgeCost);
            // printf("Neighbor added: id %d cost %lf\n", neighbours[nrNeighbours], costs[nrNeighbours]);
            nrNeighbours++;
            updateLowestCostEdges(edgeCost);
            
            if( neighbourId == 0 )
            {
                this->connectsToStart = 1;
            }
        }

        // Returns the road cost between this city and the city specified by the 'neighbourId' argument
        double getEdgeCost(int neighbourId)
        {
            for ( int i = 0 ; i < nrNeighbours ; i++ )
            {
                if ( neighbours[i] == neighbourId )
                {
                    return costs[i];
                }
            }
            return -1.0;
        }

        // Checks to see if the received edge id bigger than the ones already stored. If so it changes the smallest
        void updateLowestCostEdges(double newEdge)
        {
            if( newEdge < lowestCostEdges[0] )
            {
                lowestCostEdges[1] = lowestCostEdges[0];
                lowestCostEdges[0] = newEdge;
            }
            else
            {
                if ( newEdge < lowestCostEdges[1] )
                {
                    lowestCostEdges[1] = newEdge;
                }
            }
        }

        // Returns the sum of the two lowest cost edges
        double getLowestCostEdgesSum()
        {
            return ( lowestCostEdges[0] + lowestCostEdges[1] ) ;
        }

        // Returns the highst cost edge of the two lowest ones
        double getHigherLowerTruncatedCostEdge(double roadCost)
        {
            double edge = -1;
            for ( int i = 0 ; i < 2 ; i++ )
            {
                if ( this->getLowestCostEdges()[i] > edge && this->getLowestCostEdges()[i] <= roadCost )
                {
                    edge = this->getLowestCostEdges()[i];
                }
            }
            return edge;
        }


        // Returns the road cost between two cities. -1 if the connection doesnt exist
        double getRoadCost(int neighbourId)
        {
            for ( int i = 0 ; i < nrNeighbours ; i++ )
            {
                if ( this->neighbours[i] == neighbourId )
                {
                    return this->costs[i];
                }
            }
            return -1.0;
        } 


        int getConnectsToStart() const {
            return this->connectsToStart;
        }

        // Setter and getter functions for id
        void setId(int city_id) {
            id = city_id;
        }

        int getId() const {
            return id;
        }
    
        // Setter and getter functions for maxNeighbours
        void setNrNeighbours(int city_nrNeighbours) {
            nrNeighbours = city_nrNeighbours;
        }
        int getNrNeighbours() const {
            return nrNeighbours;
        }
    
        // Setter and getter functions for neighbours
        void setNeighbours(std::vector<int> city_neighbours) {
            neighbours = city_neighbours;
        }
        std::vector<int> getNeighbours() const {
            return neighbours;
        }
    
        // Setter and getter functions for costs
        void setCosts(std::vector<double> city_costs) {
            costs = city_costs;
        }

        std::vector<double> getCosts() const {
            return costs;
        }
    
        // Setter and getter functions for highestCostEdges
        void setHighestCostEdges(double* city_highestCostEdges) {
            lowestCostEdges = city_highestCostEdges;
        }

        double* getLowestCostEdges() const {
            return lowestCostEdges;
        }
        
        // toString method
        void toString() {
            printf("Node (id = %d, nrNeighbours = %d, neighbours = [", id, nrNeighbours);
            for (int i = 0; i < nrNeighbours; i++) {
                printf("%d, ", neighbours[i]);
            }
            printf("], costs=[");
            for (int i = 0; i < maxNeighbours; i++) {
                printf("%lf, ", costs[i]);
            }
            printf("], highestCostEdges=[%lf, %lf])\n", lowestCostEdges[0], lowestCostEdges[1]);
            return;
        }
};

#endif