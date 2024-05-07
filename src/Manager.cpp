#include "Manager.h"

void Manager::readEdges(std::string path) {
    std::fstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }


    std::string line;

    //if (path[5] != '_') getline(file, line); // Ignore header

    while (getline(file, line)) {
        // Extracting Info
        std::istringstream ss(line);
        unsigned int origin, destiny;//'s child
        double distance;
        ss >> origin;
        ss.ignore(1);
        ss >> destiny;
        ss.ignore(1);
        ss >> distance;
        ss.ignore(1);

        graph.addBidirectionalEdge(Location(origin), Location(destiny), distance);
    }
}

void Manager::readNodes(std::string path, int number_vertex) {
    std::fstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::string line;
    getline(file, line); // Ignore header

    for (int i = 0; i < number_vertex; i++) {
        getline(file, line);
        unsigned int id;
        double longitude, latitude;
        std::istringstream ss(line);
        ss >> id;
        ss.ignore(1);
        ss >> longitude;
        ss.ignore(1);
        ss >> latitude;
        ss.ignore(1);
        Location vertex(id, longitude, latitude);
        graph.addVertex(vertex);
    }
}

void Manager::readToyNodes(std::string path) {
    std::fstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::string line;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string originLabel, destinyLabel;
        unsigned int src, dest;
        double distance;
        ss >> src;
        ss.ignore(1);
        ss >> dest;
        ss.ignore(1);
        ss >> distance;
        ss.ignore(1);
        Location source(src);
        Location destiny(dest);
        if (path[5] == 't') {
            getline(ss, originLabel,',');
            ss >> destinyLabel;
            source = Location(src, originLabel);
            destiny = Location(dest, destinyLabel);
        };
        auto s = graph.findVertex(source);
        auto d = graph.findVertex(destiny);
        if (s == NULL) graph.addVertex(source);
        if (d == NULL) graph.addVertex(destiny);
        if (!graph.addBidirectionalEdge(source, destiny, distance)) cout << "ERROR" << endl;
    }

}

double Manager::convert_to_radians(double coord) {
    return (coord * 3.1416) / 180;
}

double Manager::Haversine(double lat1, double lon1, double lat2, double lon2) {
    double rad_lat1 = convert_to_radians(lat1);
    double rad_lon1 = convert_to_radians(lon1);
    double rad_lat2 = convert_to_radians(lat2);
    double rad_lon2 = convert_to_radians(lon2);

    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    double aux = (sin(delta_lat/2) * sin(delta_lat/2)) + cos(rad_lat1) * cos(rad_lat2) * (sin(delta_lon/2) * sin(delta_lon/2)) ;
    double c = 2.0 * atan2 ( sqrt(aux), sqrt(1.0-aux));
    double earthradius = 6371000;
    return earthradius * c ;
}

bool Manager::crescente(Edge<Location> *primeiro, Edge<Location> *segundo) {
    return primeiro->getWeight() < segundo->getWeight();
}

void Manager::dfsKruskalPath(Vertex<Location> *v, vector<Edge<Location>*> &preorder) {
    v->setVisited(true);
    for (Edge<Location> *e : v->getAdj()) {
        Vertex<Location> *w = e->getDest();
        if (e->isSelected() && !w->isVisited()) {
            preorder.push_back(e);
            dfsKruskalPath(w, preorder);
        }
    }
    for (Edge<Location> *e : v->getIncoming()) {
        Vertex<Location> *x = e->getOrig();
        if (e->isSelected() && !x->isVisited()) {
            preorder.push_back(e);
            dfsKruskalPath(x, preorder);
        }
    }
}

void Manager::kruskal() {
    UFDS ufds(graph.getNumVertex());

    vector<Edge<Location>*> vec;

    for (Vertex<Location> *v : graph.getVertexSet()) {
        v->setVisited(false);
        for (Edge<Location> *e : v->getAdj()) {
            e->setSelected(false);
        }
    }

    for (Vertex<Location> *v : graph.getVertexSet()) {
        for (Edge<Location> *e : v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getInfo().getId() < e->getDest()->getInfo().getId()) {
                vec.push_back(e);
            }
        }
    }

    std::sort(vec.begin(), vec.end(), Manager::crescente);

    for (Edge<Location> *e : vec) {
        if (ufds.findSet(e->getOrig()->getInfo().getId()) != ufds.findSet(e->getDest()->getInfo().getId())) {
            ufds.linkSets(e->getOrig()->getInfo().getId(), e->getDest()->getInfo().getId());
            e->setSelected(true);
        }
    }

    vector<Edge<Location>*> preorder;
    dfsKruskalPath(graph.getVertexSet().at(0), preorder);

    unordered_set<int> visitedVertices;
    visitedVertices.insert(0);
    int last_inserted = 0;
    double caixa = 0;
    bool adicionou;
    for (Edge<Location> *e : preorder) {
        if (visitedVertices.find(e->getDest()->getInfo().getId()) == visitedVertices.end()) {
            if (last_inserted == e->getOrig()->getInfo().getId()) {
                caixa += e->getWeight();
            }
            else {
                adicionou = false;
                Vertex<Location> *temp = graph.findVertex(last_inserted);
                for (Edge<Location> *edge : temp->getAdj()) {
                    if (edge->getDest()->getInfo().getId() == e->getDest()->getInfo().getId()) {
                        caixa += edge->getWeight();
                        adicionou = true;
                    }
                }
                if (!adicionou) {
                    caixa += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(),
                                       e->getDest()->getInfo().getLatitude(), e->getDest()->getInfo().getLongitude());
                }
            }
            visitedVertices.insert(e->getDest()->getInfo().getId());
            last_inserted = e->getDest()->getInfo().getId();
        }
        if (visitedVertices.find(e->getOrig()->getInfo().getId()) == visitedVertices.end()) {
            visitedVertices.insert(e->getOrig()->getInfo().getId());
            if (last_inserted == e->getDest()->getInfo().getId()) {
                caixa += e->getWeight();
            }
            else {
                adicionou = false;
                Vertex<Location> *temp = graph.findVertex(last_inserted);
                for (Edge<Location> *edge : temp->getAdj()) {
                    if (edge->getDest()->getInfo().getId() == e->getOrig()->getInfo().getId()) {
                        caixa += edge->getWeight();
                        adicionou = true;
                    }
                }
                if (!adicionou) {
                    caixa += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(),
                                       e->getOrig()->getInfo().getLatitude(), e->getOrig()->getInfo().getLongitude());
                }
            }
            visitedVertices.insert(e->getOrig()->getInfo().getId());
            last_inserted = e->getOrig()->getInfo().getId();
        }
    }
    adicionou = false;
    Vertex<Location> *temp = graph.findVertex(last_inserted);
    for (Edge<Location> *e : temp->getAdj()) {
        if (e->getDest()->getInfo().getId() == 0) {
            caixa += e->getWeight();
            adicionou = true;
        }
    }
    if (!adicionou) {
        caixa += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(), graph.findVertex(0)->getInfo().getLatitude(),
                           graph.findVertex(0)->getInfo().getLongitude());
    }
    std::cout << caixa << endl;
}

void Manager::Backtracking() {}
void Manager::Triangular_Heuristic() {
    kruskal();
}
void Manager::Other_Heuristics() {}
void Manager::Traveling_Salesman() {}