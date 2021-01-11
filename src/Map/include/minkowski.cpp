//
// Created by atta on 1/11/21.
//

#include "minkowski.hpp"

namespace map {

    // Print 2D vectors coordinate values
    void minkowski::print2DVector(std::vector<std::vector<double> > vec)
    {
        for (int i = 0; i < vec.size(); ++i) {
            std::cout << "(";
            for (int j = 0; j < vec[0].size(); ++j) {
                minkowski::plotXLimMin = std::min(vec[i][j]-2.0, minkowski::plotXLimMin);
                minkowski::plotyLimMin = std::min(vec[i][j]-2.0, minkowski::plotyLimMin);
                minkowski::plotXLimMax = std::max(vec[i][j]+2.0, minkowski::plotXLimMax);;
                minkowski::plotyLimMax = std::max(vec[i][j]+2.0, minkowski::plotyLimMax);
                if (vec[i][j] >= 0)
                    std::cout << vec[i][j] << "  ";
                else
                    std::cout << "\b" << vec[i][j] << "  ";
            }
            std::cout << "\b\b)" << std::endl;
        }
    }

    // Check for duplicate coordinates inside a 2D vector and delete them
    std::vector<std::vector<double> > minkowski::delete_duplicate(std::vector<std::vector<double> > C)
    {
        // Sort the C vector
        sort(C.begin(), C.end());
        // Initialize a non duplicated vector
        std::vector<std::vector<double> > Cn;
        for (int i = 0; i < C.size() - 1; i++) {
            // Check if it's a duplicate coordinate
            if (C[i] != C[i + 1]) {
                Cn.push_back(C[i]);
            }
        }
        Cn.push_back(C[C.size() - 1]);
        return Cn;
    }

    // Com pute the minkowski sum of two vectors
    std::vector<std::vector<double> > minkowski::minkowski_sum(std::vector<std::vector<double> > A, std::vector<std::vector<double> > B)
    {
        std::vector<std::vector<double> > C;
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < B.size(); j++) {
                // Compute the current sum
                std::vector<double> Ci = { A[i][0] + B[j][0], A[i][1] + B[j][1] };
                // Push it to the C vector
                C.push_back(Ci);
            }
        }
        C = delete_duplicate(C);
        return C;
    }

    // Compute the centroid of a polygon
    std::vector<double> minkowski::compute_centroid(std::vector<std::vector<double> > vec)
    {
        std::vector<double> centroid(2);
        double centroid_x=0, centroid_y=0;
        for (int i = 0; i < vec.size(); i++) {
            centroid_x += vec[i][0];
            centroid_y += vec[i][1];
        }
        centroid[0] = centroid_x / vec.size();
        centroid[1] = centroid_y / vec.size();
        return centroid;
    }

    // Compute the angle of each point with respect to the centroid and append in a new column
    // Resulting vector[xi,yi,anglei]
    std::vector<std::vector<double> > minkowski::compute_angle(std::vector<std::vector<double> > vec)
    {
        std::vector<double> centroid = compute_centroid(vec);
        double prec = 0.0001;
        for (int i = 0; i < vec.size(); i++) {
            double dy = vec[i][1] - centroid[1];
            double dx = vec[i][0] - centroid[0];
            // If the point is the centroid then delete it from the vector
            if (abs(dx) < prec && abs(dy) < prec) {
                vec.erase(vec.begin() + i);
            }
            else {
                // compute the centroid-point angle
                double theta = (atan2(dy, dx) * 180) / M_PI;
                // append it to the vector in a 3rd column
                vec[i].push_back(theta);
            }
        }
        return vec;
    }

    // Sort the vector in increasing angle (clockwise) for plotting
    std::vector<std::vector<double> > minkowski::sort_vector(std::vector<std::vector<double> > vec)
    {
        std::vector<std::vector<double> > sorted_vec = compute_angle(vec);
        // Change the 0 angle to 90 degrees
        for (int i = 0; i < sorted_vec.size(); i++) {
            if (sorted_vec[i][2] == 0)
                sorted_vec[i][2] = 90.0;
        }
        // Sort with respect to the 3rd column(angles)
        sort(sorted_vec.begin(),
             sorted_vec.end(),
             [](const std::vector<double>& a, const std::vector<double>& b) {
                 return a[2] < b[2];
             });
        return sorted_vec;
    }

    // Process the shapes and plot them
    void minkowski::plot(std::vector<std::vector<double> > vec, std::string color)
    {
        // Sort the vector coordinates in clockwise
        std::vector<std::vector<double> > sorted_vec;
        sorted_vec = sort_vector(vec);
        // Add the first element to the end of the vector
        sorted_vec.push_back(sorted_vec[0]);
        // Loop through vector original size
        for (int i = 0; i < sorted_vec.size() - 1; i++) {
            // Connect coordinate point and plot the lines (x1,x2)(y1,y2)
            matplot::plot({ sorted_vec[i][0], sorted_vec[i + 1][0] }, { sorted_vec[i][1], sorted_vec[i + 1][1] }, color);
        }
    }

    // Translate the configuration space toward the obstacle
    std::vector<std::vector<double> > minkowski::shift_space(std::vector<std::vector<double> > B, std::vector<std::vector<double> > C)
    {
        // Compute the obstacle and space centroids
        std::vector<double> centroid_obstacle = compute_centroid(B);
        std::vector<double> centroid_space = compute_centroid(C);

        // Compute the translations deltas
        double dx = centroid_space[0] - centroid_obstacle[0];
        double dy = centroid_space[1] - centroid_obstacle[1];

        // Translate the space
        for (int i = 0; i < C.size(); i++) {
            C[i][0] = C[i][0] - dx;
            C[i][1] = C[i][1] - dy;
        }
        return C;
    }

    // Draw A, B and C shapes
    void minkowski::draw_shapes(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B, std::vector<std::vector<double>> C)
    {
        //Graph Format
        matplot::figure(1);

        matplot::title("Minkowski Sum");
        matplot::xlim({minkowski::plotXLimMin, minkowski::plotXLimMax});
        matplot::ylim({minkowski::plotyLimMin, minkowski::plotyLimMax});
        matplot::grid(true);

        // Draw triangle A
        matplot::hold(matplot::on);
        plot(A, "b-");

        // Draw triangle B
        matplot::hold(matplot::on);
        plot(B, "r-");

        // Draw configuration space C
        // Trasnlate the C space
        std::vector<std::vector<double> > shifted_C = shift_space(B, C);
        matplot::hold(matplot::on);
        plot(shifted_C, "k-");

        // Plot the original C shape
        matplot::hold(matplot::on);
        plot(C, "g-");

        matplot::show();

        //Save the image and close the plot
        matplot::save("../images/Minkowski_Sum.png");
    }

} //map