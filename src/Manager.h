#ifndef DA2324_PRJ1_G17_4_MANAGER_H
#define DA2324_PRJ1_G17_4_MANAGER_H


#include "Graph.h"
#include <sstream>
#include <fstream>
#include "Location.h"

class Manager {
private:
    Graph<Location> graph;
public:
    /**
 * @brief Reads data set from a CSV file.
 *
 * Complexity:
 *
 * @param number_edges Choose the number of edges for your medium-sized graph dataset.
 */
    void readEdges(std::string path);
    void readNodes(std::string path, int number_vertex);

    void Backtracking();
    void Triangular_Heuristic();
    void Other_Heuristics();
    void Traveling_Salesman();
};


#endif //DA2324_PRJ1_G17_4_MANAGER_H
