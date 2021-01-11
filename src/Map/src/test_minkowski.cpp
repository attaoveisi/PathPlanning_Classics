#include "minkowski.hpp"

int main()
{
    // Define the coordinates of triangle A and B in 2D vectors
    std::vector<std::vector<double>> A(3, std::vector<double>(2));
    // Robot A
    A = {{ 0, -1 }, { 0, 1 }, { 1, 0 }, {-2, 0}};
    std::vector<std::vector<double>> B(3, std::vector<double>(2));
    // Obstacle B
    B = {{ 0, 0 }, { 2, 2 }, { 1, -1 }, {2, 1}, {2, -1}};

    // Translating Robot toward the obstacle
    map::minkowski _map;
    A = _map.shift_space(B, A);

    // Compute the Minkowski Sum of triangle A and B
    std::vector<std::vector<double>> C;
    C = _map.minkowski_sum(A, B);

    // Print the resulting vector
    _map.print2DVector(C);

    // Draw all the shapes
    _map.draw_shapes(A, B, C);

    return 0;
}