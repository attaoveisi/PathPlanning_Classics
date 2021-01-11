/**
 * @brief A C++ program for Minkowski algorithm.
   @author Atta Oveisi
   @date Jan 2021
 */

#ifndef PATHPLANNING_CLASSICS_MINKOWSKI_H
#define PATHPLANNING_CLASSICS_MINKOWSKI_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <matplot/matplot.h>
#include <algorithm>

namespace map {
    class minkowski {
    public:

        // Print 2D vectors coordinate values
        void print2DVector(std::vector<std::vector< double>> vec);

        // Check for duplicate coordinates inside a 2D vector and delete them
        std::vector<std::vector<double>> delete_duplicate(std::vector<std::vector<double>> C);

        // Compute the minkowski sum of two vectors
        std::vector<std::vector<double>> minkowski_sum(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B);

        // Compute the centroid of a polygon
        std::vector<double> compute_centroid(std::vector<std::vector<double>> vec);

        // Compute the angle of each point with respect to the centroid and append in a new column
        // Resulting vector[xi,yi,anglei]
        std::vector<std::vector<double>> compute_angle(std::vector<std::vector<double>> vec);

        // Sort the vector in increasing angle (clockwise) for plotting
        std::vector<std::vector<double>> sort_vector(std::vector<std::vector<double>> vec);

        // Process the shapes and plot them
        void plot(std::vector<std::vector<double>> vec, std::string color);

        // Translate the configuration space toward the obstacle
        std::vector<std::vector<double>> shift_space(std::vector<std::vector<double>> B, std::vector<std::vector<double>> C);

        // Draw A, B and C shapes
        void draw_shapes(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B, std::vector<std::vector<double>> C);

    private:
        double plotXLimMin = -1.0;
        double plotyLimMin = -1.0;
        double plotXLimMax = 1.0;
        double plotyLimMax = 1.0;


    }; // minkowski

} //map


#endif //PATHPLANNING_CLASSICS_MINKOWSKI_H
