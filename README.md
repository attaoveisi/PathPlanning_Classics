# PathPlanning_Classics (This repo is under construction)
**Goal:** The path planning and graph search algorithms

## Background study

![image](https://user-images.githubusercontent.com/17289954/104181045-67a3de80-540e-11eb-9c31-03c801fa4514.png)

### Minkowski Sum

The Minkowski sum is a mathematical property that can be used to compute the configuration space given an obstacle geometry and robot geometry. 

![image](https://user-images.githubusercontent.com/17289954/104181950-f2d1a400-540f-11eb-9c3a-dbb4e71dd852.png)

For convex polygons, computing the convolution is trivial and can be done in linear time - however for non-convex polygons (i.e. ones with gaps or holes present), the computation is much more expensive. see [this](https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects) and [this](http://twistedoakstudios.com/blog/Post554_minkowski-sums-and-differences) for more information. A video explanation is given [here](https://www.youtube.com/watch?v=24L9z9tk6k0)

### Discretization

1) Roadmap

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

#### Voronoi Diagram


2) Cell decomposition

3) Gradient field


### Graph search


## Implemented approaches

**The search algorithms:**
- Breadth first (finished)
- Depth first (finished)
- Dijkstra (finished)
- A_star (Ongoing)
- ...
_______________________________________________________________
**Discrete optimal planning:**
- backward value iteration (Ongoing)
_______________________________________________________________
**Obstacles and map:**
- Minkowski sum

_______________________________________________________________
To use:
`git clone git clone https://github.com/attaoveisi/PathPlanning_Classics.git`

then:

`cd PathPlanning_Classics`


** Documentation is created by Doxygen. Do `doxygen Doxyfile` and go to `/docs/html/index.htm` and enjoy.
_______________________________________________________________
