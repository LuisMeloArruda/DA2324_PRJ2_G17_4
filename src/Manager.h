#ifndef DA2324_PRJ1_G17_4_MANAGER_H
#define DA2324_PRJ1_G17_4_MANAGER_H


#include "Graph.h"
#include <sstream>
#include <fstream>

class Manager {
private:
    Graph<unsigned int> graph;
public:
    /**
 * @brief Reads data set from a CSV file.
 *
 * Complexity:
 *
 * @param number_edges Choose the number of edges for your medium-sized graph dataset.
 */
    void readEdges(int number_edges);
};


#endif //DA2324_PRJ1_G17_4_MANAGER_H
