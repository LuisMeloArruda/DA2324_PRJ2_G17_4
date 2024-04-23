#include "Manager.h"

void Manager::readEdges(int number_edges) {
    std::string j;
        j = "../Data/Medium-Graphs/edges_" + std::to_string(number_edges) + ".csv";
    std::fstream file(j);

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::string line;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        // Exracting Info
        std::istringstream ss(line);
        unsigned int origin, destiny;//'s child
        double distance;
        ss >> origin;
        ss.ignore(1);
        ss >> destiny;
        ss.ignore(1);
        ss >> distance;
        ss.ignore(1);

        graph.addEdge(origin, destiny, distance);
        graph.addVertex(origin);
    }
}