# PathPlanning_Classics (This repo is under construction)
**Goal:** The path planning and graph search algorithms

## Background study

![image](https://user-images.githubusercontent.com/17289954/104181045-67a3de80-540e-11eb-9c31-03c801fa4514.png)

### Minkowski Sum

The Minkowski sum is a mathematical property that can be used to compute the configuration space given an obstacle geometry and robot geometry. 

![image](https://user-images.githubusercontent.com/17289954/104181950-f2d1a400-540f-11eb-9c3a-dbb4e71dd852.png)

For convex polygons, computing the convolution is trivial and can be done in linear time - however for non-convex polygons (i.e. ones with gaps or holes present), the computation is much more expensive. see [this](https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects) and [this](http://twistedoakstudios.com/blog/Post554_minkowski-sums-and-differences) for more information. A video explanation is given [here](https://www.youtube.com/watch?v=24L9z9tk6k0)


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
'\n'
then:
'\n'
`cd PathPlanning_Classics`
'\n'
and
'\n' 
`wstool init src/ src/include.rosinstall`


** Documentation is created by Doxygen. Do `doxygen Doxyfile` and go to `/docs/html/index.htm` and enjoy.
_______________________________________________________________
Especial thank to Nicolai Spohrer
