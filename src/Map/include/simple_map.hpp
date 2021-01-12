//
// Created by atta on 1/12/21.
//

#ifndef PATHPLANNING_SIMPLE_MAP_H
#define PATHPLANNING_SIMPLE_MAP_H

namespace map {
    class simple_map {
    public:
        const static int mapHeight = 300;
        const static int mapWidth = 150;
        vector<vector<double> > map = GetMap();
        vector<vector<int> > grid = MaptoGrid();
        vector<vector<int> > heuristic = GenerateHeuristic();

    private:
        // Read the file and get the map
        vector<vector<double> > GetMap();

        //Convert the map to 1's and 0's
        vector<vector<int> > MaptoGrid();

        // Generate a Manhattan Heuristic Vector
        vector<vector<int> > GenerateHeuristic();
    };
} //map


#endif //PATHPLANNING_SIMPLE_MAP_H
