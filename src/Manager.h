#ifndef DA2324_PRJ1_G17_4_MANAGER_H
#define DA2324_PRJ1_G17_4_MANAGER_H


#include "Graph.h"
#include <sstream>
#include <fstream>
#include "Location.h"
#include <cmath>
#include "UFDS.h"
#include <unordered_set>

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
    void readToyNodes(std::string path);

    void Backtracking();
    void Triangular_Heuristic();
    void Other_Heuristics();
    void Traveling_Salesman();

    double convert_to_radians(double cord);
    double Haversine(double lat1, double lon1, double lat2, double lon2);
    void dfsKruskalPath(Vertex<Location> *v, vector<Edge<Location>*> &preorder);

    static bool crescente(Edge<Location> *primeiro, Edge<Location> *segundo);
    void kruskal();

};


#endif //DA2324_PRJ1_G17_4_MANAGER_H
