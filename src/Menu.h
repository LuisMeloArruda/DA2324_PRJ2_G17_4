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
     * Complexity: O(2^V), where V is the number of vertices in the graph.
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
     * Complexity: O(2^V), where V is the number of vertices in the graph.
     *
     */
    void Backtracking();

    void Triangular_Heuristic();

    void TSP_NearestNeighbor();

    void TSP_NearestNeighborComplete();

private:
    Manager network;
};


#endif //DA2324_PRJ2_G17_4_MENU_H
