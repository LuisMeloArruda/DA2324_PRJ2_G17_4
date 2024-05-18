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
#include <limits.h>
#include <set>


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
     * Complexity: O(V!), where V is the number of vertices in the graph.
     *
     */
    void Backtracking();
    /**
     * @brief Auxiliary function for backtracking algorithm.
     *
     * Complexity: O(V!), where V is the number of vertices.
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
     * @brief Implements a heuristic based on the triangular inequality to approximate the Traveling Salesman Problem (TSP) solution.
     *
     * Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
     *
     */
    void Triangular_Heuristic();
    /**
     * @brief Implements other heuristics (Adapted Christofides) for the Traveling Salesman Problem (TSP).
     *
     * Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
     *
     */
    void adapted_Christofides();
     /**
    * @brief Implements other heuristics (Nearest Neighbor) for the Traveling Salesman Problem (TSP). (Assuming Fully Connected)
    *
    * Complexity: O(V^2) where V is the number of vertices in the graph.
    *
    */
    void TSP_NearestNeighborComplete();
    /**
    * @brief Implements other heuristics (Nearest Neighbor) for the Traveling Salesman Problem (TSP).
    *
    * Complexity: O(V^2) where V is the number of vertices in the graph.
    *
    */
    void TSP_NearestNeighbor();
    /**
     * @brief Finds the nearest unvisited neighbor for a given vertex and updates the path and total distance.
     *
     * Complexity: O(V^2) where V is the number of vertices in the graph.
     *
     * @param Vertice Pointer to the current vertex.
     * @param distance Reference to the total distance of the path, which will be updated.
     * @param path Reference to the path vector, which will be updated to include the visited vertices.
     *
     * @return Vertex<Location>* Pointer to the last vertex visited in the path.
     */
    Vertex<Location> *aux_NearestNeighbor(Vertex<Location> *Vertice, double &distance, std::vector<Vertex<Location>*> &path);
    /**
     * @brief Converts a coordinate from degrees to radians.
     *
     * Complexity: O(1)
     *
     * @param cord The coordinate in degrees.
     *
     * @return double Coordinate in radians.
     */
    double convert_to_radians(double cord);
    /**
     * @brief Computes the Haversine distance between two geographic coordinates.
     *
     * Complexity: O(1)
     *
     * @param lat1 Latitude of the first point.
     * @param lon1 Longitude of the first point.
     * @param lat2 Latitude of the second point.
     * @param lon2 Longitude of the second point.
     *
     * @return double Haversine distance in meters.
     */
    double Haversine(double lat1, double lon1, double lat2, double lon2);
    /**
     * @brief Depth-First Search (DFS) to find the path in the MST created by Kruskal's algorithm.
     *
     * Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
     *
     * @param v The starting vertex.
     * @param preorder The vector to store the preorder traversal of edges.
     */
    void dfsKruskalPath(Vertex<Location> *v, vector<Edge<Location>*> &preorder);
    /**
     * @brief Comparator function to sort edges in ascending order of weight.
     *
     * Complexity: O(1)
     *
     * @param primeiro The first edge.
     * @param segundo The second edge.
     *
     * @return True if the weight of the first edge is less than the weight of the second edge, false otherwise.
     */
    static bool crescente(Edge<Location> *primeiro, Edge<Location> *segundo);
    /**
    * @brief Prints the optimal path found and its cost.
    *
    * Complexity: O(V), where V is the number of vertices.
    *
    * @param path The vector containing the pointers of the sequence of locations.
    * @param cost The total cost of the path.
    */
    void printOptimalPath(vector<Vertex<Location>*> path, double cost);
    /**
     * @brief Prints the optimal path found and its cost.
     *
     * Complexity: O(V), where V is the number of vertices.
     *
     * @param path The vector containing the sequence of locations.
     * @param cost The total cost of the path.
     */
    void printOptimalPath(vector<Location> path, double cost);
    /**
     * @brief Auxiliary Depth-First Search (DFS) to find the path and cost in the graph.
     *
     * Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
     *
     * @param v The starting vertex.
     * @param path The vector to store the sequence of vertices.
     * @param cost The total cost of the path.
     */
    void auxDFS(Vertex<Location>* v, vector<Vertex<Location>*>& path, double& cost);
    /**
     * @brief Clears the graph by removing all vertices.
     *
     * Complexity: O(V), where V is the number of vertices in the graph.
     *
     */
    void clearGraph();
};


#endif //DA2324_PRJ1_G17_4_MANAGER_H
