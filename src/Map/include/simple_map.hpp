//
// Created by atta on 1/12/21.
//

#ifndef PATHPLANNING_SIMPLE_MAP_H
#define PATHPLANNING_SIMPLE_MAP_H

#include <iostream>
#include <math.h>
#include <vector>
#include <iterator>
#include <fstream>
#include <matplot/matplot.h>

namespace map {
    class simple_map {
    public:
        int mapHeight{300};
        int mapWidth{150};
        std::vector<std::vector<double>> map = GetMap();
        std::vector<std::vector<int>> grid = MaptoGrid();
        std::vector<std::vector<int>> heuristic = GenerateHeuristic();

    private:
        // Read the file and get the map
        std::vector<std::vector<double> > GetMap();

        //Convert the map to 1's and 0's
        std::vector<std::vector<int> > MaptoGrid();

        // Generate a Manhattan Heuristic Vector
        std::vector<std::vector<int> > GenerateHeuristic();
    };
} //map


#endif //PATHPLANNING_SIMPLE_MAP_H
