//
// Created by atta on 1/12/21.
//

#include "simple_map.hpp"

namespace map {
    vector<vector<double>> simple_map::GetMap()
    {
        vector<vector<double> > mymap(mapHeight, vector<double>(mapWidth));
        ifstream myReadFile;
        myReadFile.open("map.txt");

        while (!myReadFile.eof()) {
            for (int i = 0; i < mapHeight; i++) {
                for (int j = 0; j < mapWidth; j++) {
                    myReadFile >> mymap[i][j];
                }
            }
        }
        return mymap;
    }

    //Convert the map to 1's and 0's
    vector<vector<int> > simple_map::MaptoGrid()
    {
        vector<vector<int> > grid(mapHeight, vector<int>(mapWidth));
        for (int x = 0; x < mapHeight; x++) {
            for (int y = 0; y < mapWidth; y++) {
                if (map[x][y] == 0) //unkown state
                    grid[x][y] = 1;

                else if (map[x][y] > 0) //Occupied state
                    grid[x][y] = 1;

                else //Free state
                    grid[x][y] = 0;
            }
        }

        return grid;
    }

    // Generate a Manhattan Heuristic Vector
    vector<vector<int>> simple_map::GenerateHeuristic()
    {
        vector<vector<int> > heuristic(mapHeight, vector<int>(mapWidth));
        int goal[2] = { 60, 50 };
        for (int i = 0; i < heuristic.size(); i++) {
            for (int j = 0; j < heuristic[0].size(); j++) {
                int xd = goal[0] - i;
                int yd = goal[1] - j;
                // Manhattan Distance
                int d = abs(xd) + abs(yd);
                // Euclidian Distance
                // double d = sqrt(xd * xd + yd * yd);
                // Chebyshev distance
                // int d = max(abs(xd), abs(yd));
                heuristic[i][j] = d;
            }
        }
        return heuristic;
    }
}