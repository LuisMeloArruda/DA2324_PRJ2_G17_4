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
#include <iomanip>


class Manager {
private:
    Graph<Location> graph;
public:
    /**
     * @brief Reads edge information from a file and adds bidirectional edges.
     *
     * Complexity: O(n), where n is the number of edges in the file.
     *
     * @param path The path to the file containing edge information.
     */
    void readEdges(std::string path);
    /**
     * @brief Reads node information from a file and adds vertices to the graph.
     *
     * Complexity: O(n), where n is the number of nodes in the file.
     *
     * @param path The path to the file containing edge information.
     * @param number_vertex The number of vertices to read from the file.
     */
    void readNodes(std::string path, int number_vertex);
    /**
     * @brief Reads toy node information from a file and adds vertices and edges to the graph.
     *
     * Complexity: O(n), where n is the number of nodes in the file.
     *
     * @param path The path to the file containing edge information.
     */
    void readToyNodes(std::string path);
    /**
     * @brief Executes the backtracking algorithm to find an optimal path.
     *
     * Complexity: O(2^V), where V is the number of vertices in the graph.
     *
     */
    void Backtracking();
    /**
     * @brief Auxiliary function for backtracking algorithm.
     *
     * Complexity: O(2^V * E), where V is the number of vertices and E is the number of edges.
     *
     * @param count The current count of visited vertices.
     * @param currPos The current position of the vertex in the graph.
     * @param cost The current cost of the path.
     * @param ans The current optimal cost.
     * @param path The vector storing the optimal path.
     * @param aux The auxiliary vector storing the current path being explored.
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

    void printOptimalPath(vector<Location> path, double cost);

    void auxDFS(Vertex<Location>* v, vector<Vertex<Location>*>& path, double& cost);
};


#endif //DA2324_PRJ1_G17_4_MANAGER_H
