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

## Sample-Based Path Planning

In more than 2D problem, due to *Increased Dimensionality*, *Constrained Dynamics* the methods in 2D approach are not applicable.

For a 2-dimensional 8-connected space, every node has 8 successors (8-connected means that from every cell you can move laterally or diagonally). Imagine a 3-dimensional 8-connected space, how many successors would every node have? 26. As the dimension of the C-space grows, the number of successors that every cell has increases substantially. In fact, for an n-dimensional space, it is equal to 3^n - 1.

Aside from robots with many degrees of freedom and multi-robot systems, another computational difficulty involves working with robots that have constrained dynamics. For instance, a car is limited in its motion - it can move forward and backward, and it can turn with a limited turning radius - as you can see in the image below. Robotic systems can be classified into two different categories - *holonomic* and *non-holonomic*. Holonomic systems can be defined as systems where every constraint depends exclusively on the current pose and time, and not on any derivatives with respect to time. Nonholonomic systems, on the other hand, are dependent on derivatives. Path planning for nonholonomic systems is more difficult due to the added constraints.

Sample-based path planning differs from combinatorial path planning in that it does not try to systematically discretize the entire configuration space. Instead, it samples the configuration space randomly (or semi-randomly) to build up a representation of the space. The resultant graph is not as precise as one created using combinatorial planning, but it is much quicker to construct because of the relatively small number of samples used.

Such an approach is very effective in high-dimensional spaces, however it does have some downfalls. Sampling a space uniformly is not likely to reach small or narrow areas, such as the passage depicted in the image below. Since the passage is the only way to move from start to goal, it is critical that a sufficient number of samples occupy the passage, or the algorithm will return ‘no solution found’ to a problem that clearly has a solution. 

I have listed two approaches:

1) Probabilistic Roadmap Method

2) Rapidly Exploring Random Tree Method

The methods are explained below. These methods are quiet jerky and can not be readily applied on the robot, a postprocesing **smoothing** step should be carried out in order to make the path drivable.

### Probabilistic Roadmap Method (PRM)

The process consists of exploration and query. In the exploration phase, as it can be seen below, the configuration space is randomly sampled

![image](https://user-images.githubusercontent.com/17289954/104425957-94c4ce00-5581-11eb-945e-0e74ae6bb210.png)

Then, a new sample is generated (in refinement phase) and the possibility to connect with neighboring nodes is checked.

![image](https://user-images.githubusercontent.com/17289954/104424059-2717a280-557f-11eb-95e0-ff071e6a24d0.png)

Finally, if the configuration space is sparsely sampled, a search algorithm such as A* is used to find the correct path. Tha pseudo-algorithm is shown below:

![image](https://user-images.githubusercontent.com/17289954/104424205-58906e00-557f-11eb-8e61-a41de783b2b2.png)

There are several parameters in the PRM algorithm that require tweaking to achieve success in a particular application. Firstly, the number of iterations can be adjusted - the parameter controls between how detailed the resultant graph is and how long the computation takes. Another decision that a robotics engineer would need to make is how to find neighbors for a randomly generated configuration. One option is to look for the k-nearest neighbors to a node. To do so efficiently, a k-d tree can be utilized - to break up the space into ‘bins’ with nodes, and then search the bins for the nearest nodes. Another option is to search for any nodes within a certain distance of the goal. Ultimately, knowledge of the environment and the solution requirements will drive this decision-making process. The choice for what type of **local planner** use is another decision that needs to be made by the robotics engineer. For most scenarios, a simple planner is preferred, as the process of checking an edge for collisions is repeated many times and efficiency is key. However, more powerful planners may be required in certain problems. In such a case, the local planner could even be another PRM. The [following](https://webspace.science.uu.nl/~gerae101/pdf/compare.pdf) link discusses several alternative strategies for implementing a PRM that may produce a more optimal path in a more efficient manner. 

The Learning Phase takes significantly longer to implement than the Query Phase, which only has to connect the start and goal nodes, and then search for a path. However, the graph created by the Learning Phase can be reused for many subsequent queries. For this reason, PRM is called a multi-query planner. This is very beneficial in static or mildly-changing environments. However, some environments change so quickly that PRM’s multi-query property cannot be exploited. In such situations, PRM’s additional detail and computational slow nature is not appreciated. A quicker algorithm would be preferred - one that doesn’t spend time going in all directions without influence by the start and goal.

### Rapidly Exploring Random Tree Method (RRT)

unlike PRM, RRT disregards a dense distribution of the node in C-space and builds individual queries-based search- It is trivial that PRM is better for static environment where the sampled environment can be used for multiple queries while RRT is thought for dynamical planning.

RRT generates one connection to each parent. If the node is within the certain distance, then it will be connected, otherwise in the same direction a node within a certain distance will be created.  

![image](https://user-images.githubusercontent.com/17289954/104426823-c38f7400-5582-11eb-82e5-26a144d48dd2.png)

The pseudo-algorithm looks like this:

![image](https://user-images.githubusercontent.com/17289954/104427216-46183380-5583-11eb-915a-b3c972fc8aee.png)

One key parameter in this method is the sampling method (ie. how a random configuration is generated) e.g., sample uniformly - which would favour wide unexplored spaces, or sample with a bias - which would cause the search to advance greedily in the direction of the goal. Greediness can be beneficial in simple planning problems, however in some environments it can cause the robot to get stuck in a local minima. It is common to utilize a uniform sampling method with a small hint of bias.

The next parameter that can be tuned is δ. As RRT starts to generate random configurations, a large proportion of these configurations will lie further than a distance δ from the closest configuration in the graph. In such a situation, a randomly generated node will dictate the direction of growth, while δ is the growth rate. Choosing a small δ will result in a large density of nodes and small growth rate. On the other hand, choosing a large δ may result in lost detail, as well as an increasing number of nodes being unable to connect to the graph due to the greater chance of collisions with obstacles. δ must be chosen carefully, with knowledge of the environment and requirements of the solution.

the RRT method supports planning for non-holonomic systems, while the PRM method does not. This is so because the RRT method can take into consideration the additional constraints (such as a car’s turning radius at a particular speed) when adding nodes to a graph, the same way it already takes into consideration how far away a new node is from an existing tree.

see [this](https://webspace.science.uu.nl/~gerae101/pdf/compare.pdf) and [this](https://www.cs.cmu.edu/~maxim/files/pathplanforMAV_icra13.pdf) for more information.

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
