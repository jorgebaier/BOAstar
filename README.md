# Bi-Objective A*, NAMOAdr, Bi-Objective Dijkstra

This is the C implementation of Bi-Objective A* (BOA*), New Approach to Multi-Objective A* with dimensionality reduction (NAMOA\*dr), and Bi-Objective Dijkstra (BOD). BOA* and NAMOA*dr computes a Pareto frontier containing paths from a given initial node to a given goal node on a given graph with two cost functions. BOD, instead, completes a Pareto frontier containing paths to every node of the graph from a given source node. More details in the following paper:

* [Carlos Hernández Ulloa, William Yeoh, Jorge A. Baier, Han Zhang, Luis Suazo, Sven Koenig:
A Simple and Fast Bi-Objective Search Algorithm. ICAPS 2020: 143-151](https://ojs.aaai.org//index.php/ICAPS/article/view/6655)

The implementation contained in this package assumes the graph is explicitly given.

# Benchmark files

The map files are stored in a separate file that you can download [from here](https://drive.google.com/file/d/1n95JsiNVCwHpQvu9kWLAlPyOUFkw9_jP/view?usp=sharing).

# Compilation

Compile using `make`.

# Running BOA*, NAMOA*dr and BOD

To run a single problem use  `./boa [graph_file] [start_node] [goal_node]` for BOA*, `./namoadr [graph_file] [start_node] [goal_node]` or `./bod [graph_file] [start_node]`, for BOD. For example: `./boa Maps/NY-road-d.txt 1 500`.

# The M3 Algorithm

The NAMOA*dr code can use the M3 algorithm for op-pruning. To enable this feature, define the M3 macro in include.h.
