## 2023-02-24

### 1 - queue.c
- When we create the queue, one of the parameters is a pointer to a function (this is because the faculty lets us create a structure in the way we prefer), and the other is a structure we created
- This function compares two structures and returns 0 (better than) or 1 (worse than)

### 2 - The Roads/Edges
- We consider there are always at least two edges/roads associated to a given city
- We cannot visit a given city twice ("exiting" the origin city for the first time does not count)

### 3 - Structures
- The number of cities will be small: do no bother storing the cities and direct travel costs (i,j) in a list instead of a matrix, it is not worth it

### 4 - Pruning
- Roads with travel costs between cities that go over the LB can automatically be discarded

### 5 - Priority
- The task manager has a priority functionality that can check and compare priority by itself, without need for the priority queue

### 6 - Compilation
- Do not forget the makefile (optimization -O3, flag -fopenmp), one for each iteration
- Executable name must be tsp

### 7 - Submission
- If we made improvements to the serial version post-delivery, we may re-submit it with the OpenMP version (if so, write the changes in the report)