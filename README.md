# DistributedComputing

Project for our Distributed and Parallel Computing class 


## Steps to Run:
### C Version
```
cd ./SerialImplementation/TravelComputer
gcc -O3 -fopenmp travelComputer.c queue.c tour.c arrayManipulation.c -o tsp
.\tsp <arg1> <arg2>
```

With `make`:
```
cd ./SerialImplementation/TravelComputer
make
.\tsp <arg1> <arg2>
```
 
### C++ Version
```
cd ./SerialImplementation/TSP
g++ -O3 -fopenmp -g -o tsp.cpp tsp 
.\tsp <arg1> <arg2>
```

With `make`:
```
cd ./SerialImplementation/TSP
make
.\tsp <arg1> <arg2>
```