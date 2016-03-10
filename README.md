# googlehashcode
An approach using C++

Running: It uses C++11 (i.e. add -std=c++11 when compiling). It reads the test case from stdin and writes solution to PATH, where PATH is the first command line argument. The second argument describes the number of "perturbations" done to the algorithm. It's probably best to set this to zero, since it doesn't improve solution by much.

The solution is rather simple greedy algorithm, where I always take one drone that isn't doing anything right now, and it chooses (warehouse, customer) pair based on some evaluation function. There's additional trick where I store the whole path of each drone, and I'm allowing to take items in any of the previously visited warehouses as long as it didn't exceed the maximum load of the drone. There are few more tricks, but they are less important. Overall, there's is still a lot of room for improvement.
