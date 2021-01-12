# PathPlanning_Classics (This repo is under construction)
**Goal:** The path planning and graph search algorithms

## Background study

![image](https://user-images.githubusercontent.com/17289954/104181045-67a3de80-540e-11eb-9c31-03c801fa4514.png)

## Minkowski Sum

The Minkowski sum is a mathematical property that can be used to compute the configuration space given an obstacle geometry and robot geometry. 

![image](https://user-images.githubusercontent.com/17289954/104181950-f2d1a400-540f-11eb-9c3a-dbb4e71dd852.png)

For convex polygons, computing the convolution is trivial and can be done in linear time - however for non-convex polygons (i.e. ones with gaps or holes present), the computation is much more expensive. see [this](https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects) and [this](http://twistedoakstudios.com/blog/Post554_minkowski-sums-and-differences) for more information. A video explanation is given [here](https://www.youtube.com/watch?v=24L9z9tk6k0)

## Discretization

### **Roadmap**

These methods represent the configuration space using a simple connected graph - similar to how a city can be represented by a metro map. 

![image](https://user-images.githubusercontent.com/17289954/104284463-590f0300-54b2-11eb-97aa-670c368d42d4.png)

Roadmap methods are typically implemented in two phases:

- The **construction phase** builds up a graph from a continuous representation of the space. This phase usually takes a significant amount of time and effort, but the resultant graph can be used for multiple queries with minimal modifications.

- The **query phase** evaluates the graph to find a path from a start location to a goal location. This is done with the help of a search algorithm.

#### Visibility Graph

The Visibility Graph builds a roadmap by connecting the start node, all of the obstacles’ vertices, and goal node to each other - except those that would result in collisions with obstacles. The Visibility Graph has its name for a reason - it connects every node to all other nodes that are ‘visible’ from its location. 

![image](https://user-images.githubusercontent.com/17289954/104284811-f1a58300-54b2-11eb-8d0c-18a09e11044e.png)

The motivation for building Visibility Graphs is that the shortest path from the start node to the goal node will be a piecewise linear path that bends only at the obstacles’ vertices. This makes sense intuitively - the path would want to hug the obstacles’ corners as tightly as possible, as not to add any additional length. 

Planning on a graph rather than a cell decomposition is a fantastic way to improve the performance of path and motion planning algorithms. However, many algorithms that deal with computational geometry are fraught with challenges

![image](https://user-images.githubusercontent.com/17289954/104284902-18fc5000-54b3-11eb-9848-568b8a55ca93.png)

see [this](https://github.com/TaipanRex/pyvisgraph/tree/master/pyvisgraph) implementation in python.
Alse [this](https://github.com/rowanwins/visibility-graph) and [this](https://github.com/kevinzg/spholes)

#### Voronoi Diagram

Another discretization method that generates a roadmap is called the Voronoi Diagram. Unlike the visibility graph method which generates the shortest paths, Voronoi Diagrams maximize clearance between obstacles.

A Voronoi Diagram is a graph whose edges bisect the free space in between obstacles. Every edge lies equidistant from each obstacle around it - with the greatest amount of clearance possible. You can see a Voronoi Diagram for our configuration space in the graphic below. 

![image](https://user-images.githubusercontent.com/17289954/104288253-d7ba6f00-54b7-11eb-9fe3-b4790e9b0dac.png)#

### **Cell decomposition**

Cell decomposition divides the space into discrete cells, where each cell is a node and adjacent cells are connected with edges. There are two distinct types of cell decomposition:

- Exact Cell Decomposition
- Approximate Cell Decomposition

Exact cell decomposition divides the space into non-overlapping cells. This is commonly done by breaking up the space into triangles and trapezoids, which can be accomplished by adding vertical line segments at every obstacle’s vertex.

![image](https://user-images.githubusercontent.com/17289954/104288552-3f70ba00-54b8-11eb-9279-2ca8063cdd46.png)

To implement exact cell decomposition, the algorithm must order all obstacle vertices along the x-axis, and then for every vertex determine whether a new cell must be created or whether two cells should be merged together. Such an algorithm is called the *Plane Sweep algorithm*. 

Approximate cell decomposition divides a configuration space into discrete cells of simple, regular shapes - such as rectangles and squares (or their multidimensional equivalents). Aside from simplifying the computation of the cells, this method also supports hierarchical decomposition of space (more on this below). 

#### **Simple Decomposition**

A 2-dimensional configuration space can be decomposed into a grid of rectangular cells. Then, each cell could be marked full or empty, as before. A search algorithm can then look for a sequence of free cells to connect the start node to the goal node.

Such a method is more efficient than exact cell decomposition, but it loses its completeness. It is possible that a particular configuration space contains a feasible path, but the resolution of the cells results in some of the cells encompassing the path to be marked ‘full’ due to the presence of obstacles. A cell will be marked ‘full’ whether 99% of the space is occupied by an obstacle or a mere 1%. Evidently, this is not practical. 

#### **Iterative Decomposition**

An alternate method of partitioning a space into simple cells exists. Instead of immediately decomposing the space into small cells of equal size, the method recursively decomposes a space into four quadrants. Each quadrant is marked full, empty, or a new label called ‘mixed’ - used to represent cells that are somewhat occupied by an obstacle, but also contain some free space. If a sequence of free cells cannot be found from start to goal, then the mixed cells will be further decomposed into another four quadrants. Through this process, more free cells will emerge, eventually revealing a path if one exists.

The 2-dimensional implementation of this method is called quadtree decomposition. It can be seen in the graphic below

![image](https://user-images.githubusercontent.com/17289954/104289238-316f6900-54b9-11eb-9819-23241bb504ca.png)

![image](https://user-images.githubusercontent.com/17289954/104289424-68de1580-54b9-11eb-97ce-f842027cf7b9.png)

### **Potential field**

the potential field method generates two functions - one that attracts the robot to the goal and one that repels the robot away from obstacles. The two functions can be summed to create a discretized representation. By applying an optimization algorithm such as gradient descent, a robot can move toward the goal configuration while steering around obstacles. 

The *attractive potential field* is a function with the global minimum at the goal configuration. If a robot is placed at any point and required to follow the direction of steepest descent, it will end up at the goal configuration. This function does not need to be complicated, a simple quadratic function can achieve all of the requirements discussed above.

![image](https://user-images.githubusercontent.com/17289954/104290150-4993b800-54ba-11eb-8898-726649035499.png)

The *repulsive potential field* is a function that is equal to zero in free space, and grows to a large value near obstacles. One way to create such a potential field is with the function below. 

![image](https://user-images.githubusercontent.com/17289954/104290352-89f33600-54ba-11eb-82cf-e4e5296b0c1b.png)

Where the function ρ(x) returns the distance from the robot to its nearest obstacle, ρ0 is a scaling parameter that defines the reach of an obstacle’s repulsiveness, and ν is a scaling parameter. 

![image](https://user-images.githubusercontent.com/17289954/104290572-ca52b400-54ba-11eb-8f7b-76b9ea831ae6.png)

## Graph search

The **time complexity** of an algorithm assesses how long it takes an algorithm to generate a path, usually with respect to the number of nodes or dimensions present. It can also refer to the trade-off between quality of an algorithm (ex. completeness) vs its computation time.

The **space complexity** of an algorithm assesses how much memory is required to execute the search. Some algorithms must keep significant amounts of information in memory throughout their run-time, while others can get away with very little.

The **generality** of an algorithm considers the type of problems that the algorithm can solve.

- Breadth first
- Depth first
- Dijkstra
- A_star

![image](https://user-images.githubusercontent.com/17289954/104340676-3c49ee00-54f9-11eb-8934-0228a8d62b60.png)

for nice extensions on A* take a look at [this](http://theory.stanford.edu/~amitp/GameProgramming/Variations.html) and [this](https://movingai.com/astar-var.html)

an online tool to see the differences avaialable [here](https://qiao.github.io/PathFinding.js/visual/)

## Implemented approaches

**The search algorithms:**
- Breadth first 
- Depth first 
- Dijkstra 
- A_star 
- ...

_______________________________________________________________
**Obstacles and map:**
- Minkowski sum 

_______________________________________________________________
To use:
`git clone git clone https://github.com/attaoveisi/PathPlanning_Classics.git`


** Documentation is created by Doxygen. Do `doxygen Doxyfile` and go to `/docs/html/index.htm` and enjoy.
_______________________________________________________________
