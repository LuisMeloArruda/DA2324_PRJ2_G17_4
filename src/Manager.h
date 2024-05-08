#ifndef DA2324_PRJ1_G17_4_MANAGER_H
#define DA2324_PRJ1_G17_4_MANAGER_H


#include "Graph.h"
#include "Location.h"
#include "UFDS.h"
#include <sstream>
#include <fstream>
#include <cmath>
#include <unordered_set>
#include <float.h>


class Manager {
private:
    Graph<Location> graph;
public:
    /**
     * @brief
     *
     * Complexity:
     *
     * @param path
     */
    void readEdges(std::string path);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param path
     * @param number_vertex
     */
    void readNodes(std::string path, int number_vertex);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param path
     */
    void readToyNodes(std::string path);
    /**
     * @brief
     *
     * Complexity:
     *
     */
    void Backtracking();
    /**
     * @brief
     *
     * Complexity:
     *
     * @param count
     * @param currPos
     * @param cost
     * @param ans
     * @param path
     * @param aux
     */
    void auxBacktracking(unsigned int count, Vertex<Location>* currPos, double cost, double &ans, vector<Location> &path, vector<Location> &aux);
    /**
     * @brief
     *
     * Complexity:
     *
     */
    void Triangular_Heuristic();

    void Other_Heuristics();

    void Traveling_Salesman();
    /**
     * @brief
     *
     * Complexity:
     *
     * @param cord
     * @return
     */
    double convert_to_radians(double cord);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param lat1
     * @param lon1
     * @param lat2
     * @param lon2
     * @return
     */
    double Haversine(double lat1, double lon1, double lat2, double lon2);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param v
     * @param preorder
     */
    void dfsKruskalPath(Vertex<Location> *v, vector<Edge<Location>*> &preorder);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param primeiro
     * @param segundo
     * @return
     */
    static bool crescente(Edge<Location> *primeiro, Edge<Location> *segundo);

};


#endif //DA2324_PRJ1_G17_4_MANAGER_H
