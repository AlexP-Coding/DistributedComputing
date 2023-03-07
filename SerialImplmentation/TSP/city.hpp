#include <iostream>
class City
{
    private:
    int fillPos;
    int id;
    int numNeighbours;
    int* neighbours;
    double* costs;
    double* highestCostEdges;

public:
City(){}

// Constructor of class City
City(int id, int numCities)
{
    this->id = id;
    this->numNeighbours = numCities-1;
    this->neighbours = new int[numCities-1];
    this->costs = new double[numCities-1];
    this->highestCostEdges = new double[2];

    fillPos=0;
}

// Deconstructor of class City
~City()
{
    delete[] neighbours;
    delete[] costs;
}

// Adds a neighbour to the 'neighbours' array and a cost at the same position on to the 'costs' array
void addNeighbour(int neighbourId, double edgeCost)
{
    this->neighbours[fillPos]=neighbourId;
    this->costs[fillPos]=edgeCost;
    fillPos++;
    updateHighestCostEdges(edgeCost);
}

// Returns the road cost between this city and the city specified by the 'neighbourId' argument
double getEdgeCost(int neighbourId)
{
    for ( int i = 0 ; i < this->numNeighbours ; i++ )
    {
        if ( this->neighbours[i] == neighbourId )
        {
            return this->costs[i];
        }
    }
    return -1.0;
}

// Checks to see if the received edge id bigger than the ones already stored. If so it changes the smallest
void updateHighestCostEdges(double newEdge)
{
    if( newEdge > this->highestCostEdges[0] )
    {
        this->highestCostEdges[1] = this->highestCostEdges[0];
        this->highestCostEdges[0] = newEdge;
    }
    else
    {
        if ( newEdge > this->highestCostEdges[1] )
        {
            this->highestCostEdges[1] = newEdge;
        }
    }
}

double getHighestCostEdgesSum()
{
    return ( this->highestCostEdges[0] + this->highestCostEdges[1] ) ;
}


    // Setter and getter functions for id
    void setId(int id) {
        this->id = id;
    }
    int getId() const {
        return id;
    }

    // Setter and getter functions for numNeighbours
    void setNumNeighbours(int numNeighbours) {
        this->numNeighbours = numNeighbours;
    }
    int getNumNeighbours() const {
        return numNeighbours;
    }

    // Setter and getter functions for neighbours
    void setNeighbours(int* neighbours) {
        this->neighbours = neighbours;
    }
    int* getNeighbours() const {
        return neighbours;
    }

    // Setter and getter functions for costs
    void setCosts(double* costs) {
        this->costs = costs;
    }
    double* getCosts() const {
        return costs;
    }

    // Setter and getter functions for highestCostEdges
    void setHighestCostEdges(double* highestCostEdges) {
        this->highestCostEdges = highestCostEdges;
    }
    double* getHighestCostEdges() const {
        return highestCostEdges;
    }

    // toString method
    void toString() {
        std::cout << "Node(id=" << this->id << ", numNeighbours=" << this->numNeighbours << ", neighbours=[";
        for (int i = 0; i < this->numNeighbours; i++) {
            std::cout << this->neighbours[i];
            if (i < this->numNeighbours - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "], costs=[";
        for (int i = 0; i < this->numNeighbours; i++) {
            std::cout << this->costs[i];
            if (i < this->numNeighbours - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "], highestCostEdges=[" << this->highestCostEdges[0] << ", " << this->highestCostEdges[1] << "])";
        return;
    }
};