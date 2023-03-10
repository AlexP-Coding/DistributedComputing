#include <iostream>
#include <vector>
#include <cfloat>

#ifndef CITY_HPP
#define CITY_HPP
class City {
    private:
        int id;
        int nrNeighbours;
        int maxNeighbours;
        std::vector<int> neighbours;
        bool connectsToStart;
        double* costs;
        double* lowestCostEdges;

    public:

        City() {}

        City(int id, int nrCities) {
            this->id = id;
            this->nrNeighbours = 0;
            this->maxNeighbours = nrCities-1;
            this->connectsToStart = false;
            this->lowestCostEdges = (double*) malloc(sizeof(double)*nrCities);
            this->lowestCostEdges[0] = DBL_MAX;
            this->lowestCostEdges[1] = DBL_MAX;
            this->costs = (double*) malloc(sizeof(double)*nrCities); 

            for (int i = 0; i < maxNeighbours; i++) {
                costs[i] = -1.0;
            }
        };

        ~City() {
            std::vector<int> tempVectorInt;
            neighbours.clear();
            neighbours.swap(tempVectorInt);

            free(costs);
            free(lowestCostEdges);
        };


        void addNeighbour(int neighbourId, double edgeCost) {
            neighbours.push_back(neighbourId);
            costs[neighbourId] = edgeCost;
            nrNeighbours++;

            if (neighbourId == 0) {
                connectsToStart = true;
            }
        } 

        void setCity(int id, int nrCities) {
            this->id = id;
            this->nrNeighbours = 0;
            this->maxNeighbours = nrCities-1;
            this->connectsToStart = false;
            this->lowestCostEdges = (double*) malloc(sizeof(double)*nrCities);
            this->lowestCostEdges[0] = DBL_MAX;
            this->lowestCostEdges[1] = DBL_MAX;
            this->costs = (double*) malloc(sizeof(double)*nrCities); 

            for (int i = 0; i < maxNeighbours; i++) {
                costs[i] = -1.0;
            }
        }

        // Returns the road cost between this city and the city specified by the 'neighbourId' argument
        double getEdgeCost(int neighbourId) {
            return costs[neighbourId];
        }

        // Checks to see if the received edge id bigger than the ones already stored. If so it changes the smallest
        void updateLowestCostEdges(double newEdgeCost) {
            if( newEdgeCost < lowestCostEdges[0] ) {
                lowestCostEdges[1] = lowestCostEdges[0];
                lowestCostEdges[0] = newEdgeCost;
            }
            else if ( newEdgeCost < lowestCostEdges[1] ) {
                lowestCostEdges[1] = newEdgeCost;
            }
        }

        // Returns the sum of the two lowest cost edges
        double getLowestCostEdgesSum() {
            return ( lowestCostEdges[0] + lowestCostEdges[1] ) ;
        }

        // Returns the highest cost edge of the two lowest ones
        double getHigherLowerTruncatedCostEdge(double roadCost)
        {
            double edge = -1;
            for ( int i = 0 ; i < 2 ; i++ )
            {
                if (getLowestCostEdges()[i] > edge && getLowestCostEdges()[i] <= roadCost )
                {
                    edge = getLowestCostEdges()[i];
                }
            }
            return edge;
        }


        // Getters

        bool getConnectsToStart() {
            return connectsToStart;
        }

        int getId() {
            return id;
        }

        int getNrNeighbours() {
            return nrNeighbours;
        }

        int getMaxNeighbours() {
            return maxNeighbours;
        }

        std::vector<int> getNeighbours()  {
            return neighbours;
        }

        double* getCosts() {
            return costs;
        }

        double* getLowestCostEdges() {
            return lowestCostEdges;
        }


        // Printers

        void toString() {
            printf("City (id = %d, nrNeighbours = %d, neighbours = [", id, nrNeighbours);
            for (int i = 0; i < nrNeighbours; i++) {
                printf("%d, ", neighbours[i]);
            }
            printf("], costs=[");
            for (int i = 0; i < nrNeighbours; i++) {
                printf("%f, ", costs[neighbours[i]]);
            }
            printf("], highestCostEdges=[%f, %f])\n", lowestCostEdges[0], lowestCostEdges[1]);
            return;
        }
};
#endif
