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

void Manager::Triangular_Heuristic() {
    // RESETS THE VISITED FLAG OF VERTICES AND THE SELECTED FLAG OF EDGES IN THE GRAPH
    // PUTS THE EDGES IN A VECTOR
    vector<Edge<Location>*> vec;
    for (Vertex<Location> *v : graph.getVertexSet()) {
        v->setVisited(false);
        for (Edge<Location> *e : v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getInfo().getId() < e->getDest()->getInfo().getId()) {
                vec.push_back(e);
            }
        }
    }

    // SORTS THE EDGES INSIDE THE VECTOR IN ASCENDING ORDER OF WEIGHT
    std::sort(vec.begin(), vec.end(), Manager::crescente);

    // APPLIES UNION-FIND DATA STRUCTURE ON THE VECTOR TO ASSIGN THE SELECTED ATTRIBUTE TO THE EDGES THAT CAN BE PART OF THE MST
    UFDS ufds(graph.getNumVertex());
    for (Edge<Location> *e : vec) {
        if (ufds.findSet(e->getOrig()->getInfo().getId()) != ufds.findSet(e->getDest()->getInfo().getId())) {
            ufds.linkSets(e->getOrig()->getInfo().getId(), e->getDest()->getInfo().getId());
            e->setSelected(true);
        }
    }

    // PERFORMS A DFS ON THE GRAPH TO OBTAIN THE MST AND PUTS IT IN PREORDER
    vector<Edge<Location>*> preorder;
    dfsKruskalPath(graph.getVertexSet().at(0), preorder);

    // ALGORITHM TO ELIMINATE DUPLICATES FROM THE PREORDER AND SUM THE WEIGHT OF THE EDGES
    unordered_set<int> visitedVertices; // UNORDERED_SET TO LIMIT PASSAGE TO 1 AT EACH POINT
    visitedVertices.insert(0);
    int last_inserted = 0; // STORES THE LAST INSERTED POINT IN THE UNORDERED_SET
    double cost = 0;
    bool added;
    for (Edge<Location> *e : preorder) {
        if (visitedVertices.find(e->getDest()->getInfo().getId()) == visitedVertices.end()) { // THE NEW POINT IS IN THE DEST OF THE EDGE
            if (last_inserted == e->getOrig()->getInfo().getId()) { // IF THE LAST ADDED POINT IS IN THE SOURCE, SIMPLY ADD THE COST OF THIS EDGE
                cost += e->getWeight();
            }
            else { // IT'S A POINT IN THE SOURCE OF THE EDGE THAT HAS ALREADY BEEN ENCOUNTERED, BUT WASN'T THE LAST ONE TO BE ADDED
                added = false;
                Vertex<Location> *temp = graph.findVertex(last_inserted);
                for (Edge<Location> *edge : temp->getAdj()) { // IF IT ALREADY HAS A DECLARED DISTANCE, WE TAKE THAT ONE
                    if (edge->getDest()->getInfo().getId() == e->getDest()->getInfo().getId()) {
                        cost += edge->getWeight();
                        added = true;
                    }
                }
                if (!added) { // OTHERWISE, WE CALCULATE THE DISTANCE THROUGH LATITUDES AND LONGITUDES
                    cost += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(),
                                       e->getDest()->getInfo().getLatitude(), e->getDest()->getInfo().getLongitude());
                }
            }
            visitedVertices.insert(e->getDest()->getInfo().getId());
            last_inserted = e->getDest()->getInfo().getId();
        }
        if (visitedVertices.find(e->getOrig()->getInfo().getId()) == visitedVertices.end()) { // THE NEW POINT IS IN THE SOURCE OF THE EDGE
            visitedVertices.insert(e->getOrig()->getInfo().getId());
            if (last_inserted == e->getDest()->getInfo().getId()) { // IF THE LAST ADDED POINT IS IN THE DESTINATION, SIMPLY ADD THE COST OF THIS EDGE
                cost += e->getWeight();
            }
            else { // IT'S A POINT IN THE DESTINATION OF THE EDGE THAT HAS ALREADY BEEN ENCOUNTERED, BUT WASN'T THE LAST ONE TO BE ADDED
                added = false;
                Vertex<Location> *temp = graph.findVertex(last_inserted);
                for (Edge<Location> *edge : temp->getAdj()) { //SE ELE JÁ TEM UMA DISTANCIA DECLARADA PEGAMOS NELA
                    if (edge->getDest()->getInfo().getId() == e->getOrig()->getInfo().getId()) {
                        cost += edge->getWeight();
                        added = true;
                    }
                }
                if (!added) { // OTHERWISE, WE CALCULATE THE DISTANCE THROUGH LATITUDES AND LONGITUDES
                    cost += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(),
                                       e->getOrig()->getInfo().getLatitude(), e->getOrig()->getInfo().getLongitude());
                }
            }
            visitedVertices.insert(e->getOrig()->getInfo().getId());
            last_inserted = e->getOrig()->getInfo().getId();
        }
    }
    // CONNECT THE LAST INSERTED POINT TO THE SOURCE
    added = false;
    Vertex<Location> *temp = graph.findVertex(last_inserted);
    for (Edge<Location> *e : temp->getAdj()) {
        if (e->getDest()->getInfo().getId() == 0) {
            cost += e->getWeight();
            added = true;
        }
    }
    if (!added) {
        cost += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(), graph.findVertex(0)->getInfo().getLatitude(),
                           graph.findVertex(0)->getInfo().getLongitude());
    }
    std::cout << cost << endl;
}

void Manager::Backtracking() {
    for (Vertex<Location>* location : graph.getVertexSet()) {
        location->setVisited(false);        
    }

    Vertex<Location>* startPoint = graph.findVertex(Location(0));
    startPoint->setVisited(true);
    
    vector<Location> path(graph.getVertexSet().size()), aux(graph.getVertexSet().size());
    aux[0] = startPoint->getInfo();
    unsigned int count = 1;
    double cost = 0, ans = DBL_MAX;

    auxBacktracking(count, startPoint, cost, ans, path, aux);

    // PRINT OPTIMAL ROUTE
    cout << "The minimal route is " << ans << " meters long and is as follows:" << endl;
    for (int i = 0; i < graph.getVertexSet().size(); i++) {
        cout << "LOCATION " << i << ": " << path[i].getId();
        if (!path[i].getLabel().empty()) cout << " - " << path[i].getLabel();
        cout << endl;
    }
    cout << "LOCATION " << graph.getVertexSet().size() << ": 0";
    if (!path[0].getLabel().empty()) cout << " - " << path[0].getLabel();
    cout << endl;
}

void Manager::auxBacktracking(unsigned int count, Vertex<Location>* currPos, double cost,
                              double &ans, vector<Location> &path, vector<Location> &aux) {
    // BACKTRACKING STEP
    // Loop to traverse the adjacency list
    // of currPos node and increasing the count
    // by 1 and cost by graph[currPos][i] value
    for (Edge<Location>* edge : currPos->getAdj()) {
        // PRUNNING
        if (edge->getWeight() + cost > ans) continue;

        Vertex<Location>* v = edge->getDest();
        // Check if cycle has been found and if it is shorter than what was previously found
        if (count == graph.getVertexSet().size() && (cost + edge->getWeight() < ans) && (edge->getDest()->getInfo().getId() == 0)) {
            ans = cost + edge->getWeight();
            // Copy aux to path
            for (int i = 0; i < graph.getVertexSet().size(); i++) {
                path[i] = aux[i];
            }
            return;
        }

        if (!v->isVisited()) {
            // Mark as visited
            v->setVisited(true);
            aux[count] = v->getInfo();

            auxBacktracking(count+1, v, cost+edge->getWeight(), ans, path, aux);
            // Mark ith node as unvisited
            v->setVisited(false);
        }
    }
}