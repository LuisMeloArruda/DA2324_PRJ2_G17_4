#include "Menu.h"
#include <limits>

Menu::Menu() {
    network = Manager();
    std::cout << "\n\n"
                 "||-----------------------------||\n"
                 "||    Which Data Set Do You    ||\n"
                 "||        Want To Use ?        ||\n"
                 "||-----------------------------||\n";
    std::cout << "\nChoose an option:\n"
                 "[1] Medium-Graphs Data Set\n"
                 "[2] Toy-Graphs Data Set\n"
                 "> ";
    int option, number_edges;
    std::cin >> option;
    switch (option) {
        case 1:
            std::cout << "\nHow many edges do you want in your graph?\n"
                      << "\nOptions: [25][50][75][100][200][300][400][500][600][700][800][900]\n";
            std::cin >> number_edges;
            network.readEdges(number_edges);
            break;
        case 2:
            break;
        default:
            std::cout << "Invalid option.\n";
            Menu();
    }
    mainMenu();
}

void Menu::mainMenu() {
    while (true) {
        std::cout << "\n\n\n"
                     "||-----------------------------------------------------------------------------||\n"
                     "||   Gente descubram o easter egg que eu coloquei no trabalho, é hella funny   ||\n"
                     "||-----------------------------------------------------------------------------||\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Olá, tudo bem? Espero que sim\n"
                     "\n[0] Quit.\n"
                     "> ";
        int option;
        std::cin >> option;
        if (std::cin.fail()) {
            std::cout << "Invalid input\n"
                         "> ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mainMenu();
        } else {
            switch (option) {
                case 0:
                    exit(0);
                default:
                    std::cout << "Invalid option.\n";
                    mainMenu();
            }
        }
    }
}