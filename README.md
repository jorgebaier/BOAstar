# Bi-Objective A* and Bi-Objective Dijkstra

This is the C implementation of Bi-Objective A* (BOA*) and Bi-Objective Dijkstra (BOD). BOA* computes a Pareto frontier containing paths from a given initial node to a given goal node on a given graph with two cost functions. BOD, instead, completes a Pareto frontier containing paths to every node of the graph from a given source node. More details in the following paper:

* [Carlos Hernández Ulloa, William Yeoh, Jorge A. Baier, Han Zhang, Luis Suazo, Sven Koenig:
A Simple and Fast Bi-Objective Search Algorithm. ICAPS 2020: 143-151](https://ojs.aaai.org//index.php/ICAPS/article/view/6655)

The implementation contained in this package assumes the graph is explicitly given.

# Benchmark files

The map files are stored in a separate file that you can download [from here](https://drive.google.com/file/d/1n95JsiNVCwHpQvu9kWLAlPyOUFkw9_jP/view?usp=sharing).

# Compilation

Compile using `make`.

# Running BOA* and BOD

To run a single problem use  `./boa [graph_file] [start_node] [goal_node]` for BOA* or `./bod [graph_file] [start_node]`, for BOD. For example: `./boastar Maps/NY-road-d.txt 1 500`. 
