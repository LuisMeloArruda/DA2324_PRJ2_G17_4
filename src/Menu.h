#ifndef DA2324_PRJ2_G17_4_MENU_H
#define DA2324_PRJ2_G17_4_MENU_H

#include "Manager.h"

#include <iostream>

class Menu {
public:
    /**
     * @brief Constructor for the Menu class.
     */
    Menu();

    /**
     * @brief Displays Main Menu options.
     *
     * Complexity:
     *
     */
    int mainMenu();
    /**
     * @brief Displays Toy Graph options.
     *
     * Complexity:
     *
     */
    void ToyGraph();
    /**
     * @brief Displays Extra Fully Connected Graph options.
     *
     * Complexity:
     *
     */
    void ExtraFullyConnected();
    /**
     * @brief Displays Real World Graph options.
     *
     * Complexity:
     *
     */
    void RealWorld();
    /**
     * @brief
     *
     * Complexity:
     *
     */
    void Backtracking();

private:
    Manager network;
};


#endif //DA2324_PRJ2_G17_4_MENU_H
