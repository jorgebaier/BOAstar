# Bi-Objective A* (BOA*)

This is the C implementation of Bi-Objective A*. BOA* computes a Pareto frontier containing paths from a given initial node to a given goal node on a given graph with two cost functions. More details in the following paper:

* [Carlos Hernández Ulloa, William Yeoh, Jorge A. Baier, Han Zhang, Luis Suazo, Sven Koenig:
A Simple and Fast Bi-Objective Search Algorithm. ICAPS 2020: 143-151](https://ojs.aaai.org//index.php/ICAPS/article/view/6655)

The implementation contained in this package assumes the graph is explicitly given.

# Compilation

Compile using `make`.

# Running BOA*

To run a single problem use  `./boastar [graph_file] [start_node] [goal_node]`. For example: `./boastar ./boastar Maps/NY-road-d.txt 1 500§`.

# Running the Benchmarks

To run the benchmark problems, do as follows:

`sh script.sh Maps/NY-road-d.txt Queries/NY-queries`