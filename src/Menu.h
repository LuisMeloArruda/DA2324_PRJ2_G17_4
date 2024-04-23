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
     * @brief Displays the Main Menu options.
     *
     * Complexity:
     *
     */
    void mainMenu();

private:
    Manager network;
};


#endif //DA2324_PRJ2_G17_4_MENU_H
