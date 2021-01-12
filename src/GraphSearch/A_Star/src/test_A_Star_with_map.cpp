#include "A_Star.hpp"
#include "simple_map.hpp"

/**
 * @brief Driver program to test A*-graph search algorithm
 * 
 * @return 0 if ends 
 */

void visualization(map::simple_map map, forwardsearch::A_Star::Graph m_Graph)
{
    //Graph Format
    matplot::title("Path");
    matplot::xlim({0, (double)map.mapHeight});
    matplot::ylim({0, (double)map.mapWidth});
    std::vector<double> x_u;
    std::vector<double> y_u;
    std::vector<double> x_f;
    std::vector<double> y_f;
    std::vector<double> x_o;
    std::vector<double> y_o;

    // Draw every grid of the map:
    for (int x = 0; x < map.mapHeight; x++) {
        //std::cout << "Remaining Rows= " << map.mapHeight - x << std::endl;
        for (int y = 0; y < map.mapWidth; y++) {
            if (abs(map.map[x][y]) < 0.01) {
                //Green unkown state
                x_u.push_back(x);
                y_u.push_back(y);
            }
            else if (map.map[x][y] > 0.02) {
                //Black occupied state
                x_o.push_back(x);
                y_o.push_back(y);
            }
            else {
                //Red free state
                matplot::hold(matplot::on);
                x_f.push_back(x);
                y_f.push_back(y);
            }
        }
    }

    // Plot the robot path
    std::pair<int,int> tmp_pair;
    std::vector<int> finalPathRow;
    std::vector<int> finalPathColumn;
    int i = 0;
    while (!m_Graph.finalPath.empty())
    {
        tmp_pair = m_Graph.finalPath.top();
        finalPathRow.push_back(tmp_pair.first);
        finalPathColumn.push_back(tmp_pair.second);
        m_Graph.finalPath.pop();
        i++;
    }

    matplot::hold(matplot::on);
    matplot::plot(x_u, y_u, "g.");

    matplot::hold(matplot::on);
    matplot::plot(x_o, y_o, "k.");

    matplot::hold(matplot::on);
    matplot::plot(x_f, y_f, "r.");

    // Plot start and end states
    matplot::hold(matplot::on);
    matplot::plot({ (double)m_Graph.src.first }, { (double)m_Graph.src.second }, "bo");
    matplot::hold(matplot::on);
    matplot::plot({ (double)m_Graph.dest.first }, { (double)m_Graph.dest.second }, "b*");

    matplot::hold(matplot::on);
    matplot::plot(finalPathRow, finalPathColumn, "b.");

    //Save the image and close the plot
    matplot::show();
    matplot::save("/home/atta/PathPlanning_Classics/src/images");
}

int main()
{
	/**
	 * @brief Graph dimension
	 * 
	 */
	int n_Row = 300;
	int n_Col = 150;

	// Source is the left-most bottom-most corner 
	forwardsearch::A_Star::Graph::Pair src = std::make_pair(72, 67);

	// Destination is the left-most top-most corner 
	forwardsearch::A_Star::Graph::Pair dest = std::make_pair(225, 142);

	/**
	 * @brief Description of the Grid- 
	 * 1--> The cell is not blocked
	 * 0--> The cell is blocked
	 * 
	 */
	forwardsearch::A_Star::Graph m_Graph(n_Row, n_Col, src, dest);

    map::simple_map obj_map;
    obj_map.mapHeight = n_Row;
    obj_map.mapWidth = n_Col;
    std::vector<int> tmp_vec(n_Col);
    bool tmp_occ{false};
    for (int i = 0; i < obj_map.mapHeight; i++){
        for(int j = 0; j < obj_map.mapWidth; j++){
            if (abs(obj_map.map[i][j]) < 0.01){
                tmp_vec[j] = false;
            }else if(obj_map.map[i][j] > 0.02){
                tmp_vec[j] = false;
            }else{
                tmp_vec[j] = true;
            }
        }
        m_Graph.addRows(tmp_vec, i);
    }

	/**
	 * @brief prove that the entry is correct
	 *
	 */
	//m_Graph.printGraph();

	m_Graph.aStarSearch();

    visualization(obj_map, m_Graph);

	return 0;
}