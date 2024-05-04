#include "Menu.h"

void Menu::ToyGraph() {
    int option;
    std::string path = "../Data/Toy-Graphs/";
    while (true) {
        std::cout << "\nWhat graph?\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Shipping\n"
                     "[2] Stadiums\n"
                     "[3] Tourism\n"
                     "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                path.append("shipping.csv");
                break;
            case 2:
                path.append("stadiums.csv");
                break;
            case 3:
                path.append("tourism.csv");
                break;
            default:
                std::cout << "Invalid option.\n";
                continue;
        }
        network.readEdges(path);
        break;
    }
}

void Menu::ExtraFullyConnected() {
    int number_edges;
    std::string path = "../Data/Extra_Fully_Connected_Graphs/";
    while (true) {
        std::cout << "\nHow many edges do you want in your graph?\n"
                  << "\nOptions: [25][50][75][100][200][300][400][500][600][700][800][900]\n";
        std::cin >> number_edges;
        if (number_edges != 25 && number_edges != 50 && number_edges != 75 && number_edges != 100
            && number_edges != 200 && number_edges != 300 && number_edges != 400 && number_edges != 500
            && number_edges != 600 && number_edges != 700 && number_edges != 800 && number_edges != 900) {
            std::cout << "Choice a available option" << std::endl;
            continue;
        } else {
            network.readNodes("../Data/Extra_Fully_Connected_Graphs/nodes.csv", number_edges);
            path.append("edges_" + std::to_string(number_edges) + ".csv");
            network.readEdges(path);
            break;
        }
    }
}

void Menu::RealWorld() {
    int option, number_vertex;
    std::string path = "../Data/Real_World_Graphs/";
    std::string pathNodes = "../Data/Real_World_Graphs/";
    while (true) {
        std::cout << "\nWhat graph?\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Graph 1\n"
                     "[2] Graph 2\n"
                     "[3] Graph 3\n"
                     "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                path.append("graph1/edges.csv");
                pathNodes.append("graph2/nodes.csv");
                number_vertex = 1000;
                break;
            case 2:
                path.append("graph2/edges.csv");
                pathNodes.append("graph2/nodes.csv");
                number_vertex = 5000;
                break;
            case 3:
                path.append("graph3/edges.csv");
                pathNodes.append("graph2/nodes.csv");
                number_vertex = 10000;
                break;
            default:
                std::cout << "Invalid option.\n";
                continue;
        }
        network.readNodes(pathNodes, number_vertex);
        network.readEdges(path);
        break;
    }
}

Menu::Menu() {
    network = Manager();
    int option;
    while (true) {
        std::cout << "\n\n"
                     "||-----------------------------||\n"
                     "||    Which Data Set Do You    ||\n"
                     "||        Want To Use ?        ||\n"
                     "||-----------------------------||\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Toy-Graphs Data Set\n"
                     "[2] Extra fully connected Data Set\n"
                     "[3] Real world Data Set\n"
                     "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                ToyGraph();
                break;
            case 2:
                ExtraFullyConnected();
                break;
            case 3:
                RealWorld();
                break;
            default:
                std::cout << "Invalid option.\n";
                continue;
        }
        break;
    }
    mainMenu();
}

void Menu::mainMenu() {
    while (true) {
        std::cout << "\n\n\n"
                     "||-------------------------------------||\n"
                     "||                                     ||\n"
                     "||-------------------------------------||\n";
        std::cout << "\nChoose an option:\n"
                     "\n[0] Quit.\n"
                     "[1] Backtracking Algorithm\n"
                     "[2] Triangular Approximation Heuristic\n"
                     "[3] Other Heuristics\n"
                     "[4] Traveling Salesman in the Real World\n"
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
                case 1:
                    network.Backtracking();
                case 2:
                    network.Triangular_Heuristic();
                case 3:
                    network.Other_Heuristics();
                case 4:
                    network.Traveling_Salesman();
                default:
                    std::cout << "Invalid option.\n";
                    continue;
            }
        }
    }
}