#include <iostream>
#include <vector>

class City {
    private:
        int nrNeighbours;
        int id;
        int maxNeighbours;
        std::vector<int> neighbours;
        std::vector<double> costs;
        double* highestCostEdges;

    public:
        City(){}

        // Constructor of class City
        City(int city_id, int numCities)
        {
            id = city_id;
            maxNeighbours = numCities-1;
            highestCostEdges = new double[2];
            nrNeighbours=0;
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
            printf("Neighbor added: id %d cost %lf\n", neighbours[nrNeighbours], costs[nrNeighbours]);
            nrNeighbours++;
            updateHighestCostEdges(edgeCost);
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
        void updateHighestCostEdges(double newEdge)
        {
            if( newEdge > highestCostEdges[0] )
            {
                highestCostEdges[1] = highestCostEdges[0];
                highestCostEdges[0] = newEdge;
            }
            else
            {
                if ( newEdge > highestCostEdges[1] )
                {
                    highestCostEdges[1] = newEdge;
                }
            }
        }

        double getHighestCostEdgesSum()
        {
            return (highestCostEdges[0] + highestCostEdges[1] ) ;
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
            highestCostEdges = city_highestCostEdges;
        }
        double* getHighestCostEdges() const {
            return highestCostEdges;
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
            printf("], highestCostEdges=[%lf, %lf])\n", highestCostEdges[0], highestCostEdges[1]);
            return;
        }
};