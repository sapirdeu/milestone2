# milestone2

This part implements a server which receives a matrix as an input, with costs for each cell in the matrix, initial position and goal
position, the output is the shortest path ("cheapest" cost) from the inital position to the goal position.

The server supports multi-threading so a few clients can be handlel parallely.
The algorithms which were used to calculate the shortest path are: A*, BestFS, BFS and DFS.
After an experiment on 10 matrixes in diffrenet sizes, we analyzed the results, and the most effective algorithm was A*.
Consequently I chose A* to be the default algorithm.

## Compiling and excecuting the program:
The input is matrix written txt files with (i,j) for initial position and for goal position, finishing with the word "end".
The matrix file has to reside in the same folder of the client side.

In order to compile and run the program use the following command in the terminal:
g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
./a.out <PORT NUMBER>
notice: <PORT NUMBER> is optional, if no port is given the program will use port number 5600 as default.
