#ifndef DA2324_PRJ2_G17_4_MENU_H
#define DA2324_PRJ2_G17_4_MENU_H

#include "Manager.h"

#include <iostream>

class Menu {
public:
    /**
     * @brief Constructor for the Menu class.
     *
     * Complexity: O(1)
     */
    Menu();

    /**
     * @brief Displays Main Menu options.
     *
     * Complexity: O(V!), where V is the number of vertices in the graph.
     *
     */
    int mainMenu();
    /**
     * @brief Displays Toy Graph options.
     *
     * Complexity: O(n), where n is the number of nodes in the file.
     *
     */
    void ToyGraph();
    /**
     * @brief Displays Extra Fully Connected Graph options.
     *
     * Complexity: O(n), where n is the number of nodes in the file.
     *
     */
    void ExtraFullyConnected();
    /**
     * @brief Displays Real World Graph options.
     *
     * Complexity: O(n), where n is the number of nodes in the file.
     *
     */
    void RealWorld();
    /**
     * @brief Executes Backtracking algorithm.
     *
     * Complexity: O(V!), where V is the number of vertices in the graph.
     *
     */
    void Backtracking();
    /**
     * @brief Executes an adapted Christofides algorithm.
     *
     * Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
     *
     */
    void adapted_Christofides();
    /**
     * @brief Executes Triangular Heuristic algorithm.
     *
     * Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
     *
     */
    void Triangular_Heuristic();
    /**
     * @brief Executes Nearest Neighbor algorithm for non-connected graphs.
     *
     * Complexity: O(V^2) where V is the number of vertices in the graph.
     *
     */
    void TSP_NearestNeighbor();
    /**
     * @brief Executes Nearest Neighbor algorithm for fully connected graphs.
     *
     * Complexity: O(V^2) where V is the number of vertices in the graph.
     *
     */
    void TSP_NearestNeighborComplete();

private:
    Manager network;
    bool backtracking;
    bool shipping;
};


#endif //DA2324_PRJ2_G17_4_MENU_H
