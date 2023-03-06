class city
{
    public:
    int id;
    int numNeighbours;
    int* neighbours;
    double* costs;
    double* highestCostEdges;

    private:
    int fillPos;

// Constructor of class City
city(int id, int numCities)
{
    this->id = id;
    this->numNeighbours = numCities-1;
    this->neighbours = new int[numCities-1];
    this->costs = new double[numCities-1];
    this->highestCostEdges = new double[2];

    fillPos=0;
}

// Deconstructor of class City
~city()
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

// Returns the neighbours of this city
int* getNeighbours()
{
    return this->neighbours;
}

// Returns the costs of to the neighbours of this city
double* getCost()
{
    return this->costs;
}
};