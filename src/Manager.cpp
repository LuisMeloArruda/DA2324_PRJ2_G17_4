#include "Manager.h"

void Manager::readEdges(std::string path) {
    std::fstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }


    std::string line;

    if (path.substr(8, 10) == "Real-world") getline(file, line); // Ignore header

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

    graph.setSize(number_vertex);

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

    int size = 0;
    if (path == "../Data/Toy-Graphs/shipping.csv") size = 14;
    if (path == "../Data/Toy-Graphs/stadiums.csv") size = 11;
    if (path == "../Data/Toy-Graphs/tourism.csv") size = 5;

    graph.setSize(size);
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
        if (path == "../Data/Toy-Graphs/tourism.csv") {
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

    printOptimalPath(path, ans);
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
    // TO PRINT OUTPUT LATER
    std::vector<Vertex<Location>*> path;

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
    visitedVertices.insert(graph.getVertexSet().at(0)->getInfo().getId());
    path.push_back(graph.getVertexSet().at(0));
    int last_inserted = graph.getVertexSet().at(0)->getInfo().getId(); // STORES THE LAST INSERTED POINT IN THE UNORDERED_SET
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
            path.push_back(e->getDest());
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
                for (Edge<Location> *edge : temp->getAdj()) { // IF IT ALREADY HAS A DECLARED DISTANCE, WE TAKE THAT ONE
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
            path.push_back(e->getOrig());
            visitedVertices.insert(e->getOrig()->getInfo().getId());
            last_inserted = e->getOrig()->getInfo().getId();
        }
    }
    // CONNECT THE LAST INSERTED POINT TO THE SOURCE
    added = false;
    Vertex<Location> *temp = graph.findVertex(last_inserted);
    for (Edge<Location> *e : temp->getAdj()) {
        if (e->getDest()->getInfo().getId() == graph.getVertexSet().at(0)->getInfo().getId()) {
            cost += e->getWeight();
            added = true;
        }
    }
    if (!added) {
        cost += Haversine(temp->getInfo().getLatitude(), temp->getInfo().getLongitude(), graph.findVertex(0)->getInfo().getLatitude(),
                          graph.findVertex(0)->getInfo().getLongitude());
    }
    path.push_back(graph.getVertexSet().at(0));
    // Print found solution
    printOptimalPath(path, cost);
}

Vertex<Location> *Manager::aux_NearestNeighbor(Vertex<Location> *vertex, double &distance, std::vector<Vertex<Location>*> &path)
{
    path.push_back(vertex);
    vertex->setVisited(true);
    double lowDistance = INFINITY;
    Vertex<Location> *NextVertice = nullptr;
    for (Edge<Location> *e : vertex->getAdj())
    {
        if (e->getWeight() < lowDistance && !e->getDest()->isVisited())
        {
            lowDistance = e->getWeight();
            NextVertice = e->getDest();
        }
    }
    if (NextVertice != nullptr)
    {
        distance += lowDistance;
        return aux_NearestNeighbor(NextVertice, distance, path);
    }
    return vertex;
}

void Manager::TSP_NearestNeighborComplete() {
    // RESETS THE VISITED FLAG OF VERTICES AND THE SELECTED FLAG OF EDGES IN THE GRAPH
    for (Vertex<Location> *v : graph.getVertexSet()) {
        v->setVisited(false);
        for (Edge<Location> *e : v->getAdj()) {
            e->setSelected(false);
        }
    }

    // Place unvisited vertex in set
    std::set<int> unvisited;
    for (int i = 1; i < graph.getNumVertex(); ++i) {
        unvisited.emplace_hint(unvisited.end(), i);
    }
    std::vector<Vertex<Location>*> path;
    double distance = 0;
    Vertex<Location> *current = graph.getVertexSet().at(0);
    path.push_back(current);
    Vertex<Location> *next = nullptr;
    current->setVisited(true);
    while (current != nullptr) {
        next = nullptr;
        double nearestDistance = INFINITY;
        std::vector<int> tested(graph.getNumVertex(), 0);
        tested[current->getInfo().getId()] = 1;
        for (Edge<Location>* e : current->getAdj()) {
            tested[e->getDest()->getInfo().getId()] = 1;
            if (!e->getDest()->isVisited()) {
                if (e->getWeight() < nearestDistance) {
                    nearestDistance = e->getWeight();
                    next = e->getDest();
                }
            }
        }
        for (auto itr = unvisited.begin(); itr != unvisited.end(); itr++) {
            if (tested[*itr]) continue;
            Vertex<Location>* target = graph.findVertex(Location(*itr));
            double temp = Haversine(current->getInfo().getLatitude(), current->getInfo().getLongitude(), 
                                    target->getInfo().getLatitude(), target->getInfo().getLongitude());
            if (temp < nearestDistance) {
                nearestDistance = temp;
                next = target;
            }
        }
        if (next != nullptr) {
            distance += nearestDistance;
            path.push_back(next);
            next->setVisited(true);
            unvisited.erase(next->getInfo().getId());
        }
        current = next;
    }
    if (path.size() != graph.getNumVertex()) {
        cout << "Solution Not Found" << endl;
        return;
    }
    bool found = false;
    for (Edge<Location> *e : path.back()->getAdj()) {
        if (e->getDest() == graph.getVertexSet().at(0)) {   
            found = true;
            distance += e->getWeight();
        }
    }
    if (!found) {
        distance += Haversine(path.back()->getInfo().getLatitude(), path.back()->getInfo().getLongitude(), 
                    graph.getVertexSet().at(0)->getInfo().getLatitude(), graph.getVertexSet().at(0)->getInfo().getLongitude());
    }
    path.push_back(graph.getVertexSet().at(0));
    // Print found solution
    printOptimalPath(path, distance);
}

void Manager::TSP_NearestNeighbor() {
    // RESETS THE VISITED FLAG OF VERTICES AND THE SELECTED FLAG OF EDGES IN THE GRAPH
    for (Vertex<Location> *v : graph.getVertexSet()) {
        v->setVisited(false);
        for (Edge<Location> *e : v->getAdj()) {
            e->setSelected(false);
        }
    }

    std::vector<Vertex<Location>*> path;
    double distance = 0;
    Vertex<Location> *initialVertice = graph.getVertexSet().at(0);
    Vertex<Location> *finalVertice = aux_NearestNeighbor(initialVertice, distance, path);
    if (path.size() != graph.getNumVertex()) {
        cout << "Solution Not Found" << endl;
        return;
    }
    path.push_back(initialVertice);
    for (Edge<Location> *e : finalVertice->getAdj())
    {
        if (e->getDest() == graph.getVertexSet().at(0))
        {
            distance += e->getWeight();
        }
    }
    // Print found solution
    printOptimalPath(path, distance);
}

void Manager::adapted_Christofides() {
    // We are using an Adapted Christofides' algorithm
    // First Step: Find a Minimum Spanning Tree (set as selected the corresponding edges) -> O(E*Log(V))
    graph.MST();

    // Second Step: Get vertex with odd degree -> O(V)
    vector<Vertex<Location>*> oddDegreeVertex;
    for (Vertex<Location>* v: graph.getVertexSet()) {
        if (v->getIndegree() % 2 != 0) oddDegreeVertex.push_back(v);
    }

    // Third Step: Find Perfect Matching of odd Vertex
    graph.perfectMatch(oddDegreeVertex);

    // Fourth Step: DFS search using only selected edges and using short-cutting -> O(V+E)
    std::vector<Vertex<Location>*> path;
    double cost = 0;
    for (Vertex<Location>* v : graph.getVertexSet())
        v->setVisited(false);
    Vertex<Location>* startPoint = graph.findVertex(Location(0));
    auxDFS(startPoint, path, cost);

    // Fifth Step: Add cost of going back to beginning
    bool found = false;
    for (Edge<Location>* edge : path.back()->getAdj()) {
        if (edge->getDest() == path.front()) { // Found Connection
            cost += edge->getWeight();
            found = true;
        }
    }
    // If connection not found calculate edge "on-demand"
    if (!found) cost += Haversine(path.back()->getInfo().getLatitude(), path.back()->getInfo().getLongitude(),
                                  path.front()->getInfo().getLatitude(),  path.front()->getInfo().getLongitude());

    // Sixth Step: Print found solution
    printOptimalPath(path, cost);
}

void Manager::auxDFS(Vertex<Location>* v, vector<Vertex<Location>*>& path, double& cost) {
    v->setVisited(true);
    path.push_back(v);
    for (Edge<Location>* e : v->getAdj()) {
        if (!e->isSelected()) continue; // Ignore non-selected edges
        Vertex<Location>* w = e->getDest();
        if (!w->isVisited()) { // Exploring new node
            // Check For connection between last node and node to be explored
            bool found = false;
            for (Edge<Location>* edge : path.back()->getAdj()) {
                if (edge->getDest() == w) { // Found Connection
                    cost += edge->getWeight();
                    found = true;
                }
            }
            // If connection not found calculate edge "on-demand"
            if (!found) cost += Haversine(path.back()->getInfo().getLatitude(), path.back()->getInfo().getLongitude(),
                                         w->getInfo().getLatitude(), w->getInfo().getLongitude());
            auxDFS(w, path, cost);
        }
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

void Manager::printOptimalPath(vector<Vertex<Location>*> path, double cost) {
    for (int k = 0; k < path.size() - 1; k++)
    {
        cout << path[k]->getInfo().getId();
        if (k % 20 == 0 && k != 0) cout << " .. " << endl << " .. ";
        else cout << " ---> ";
    }
    cout << path[path.size() - 1]->getInfo().getId() << endl;
    if (path[0]->getInfo().getId() == path[path.size()-1]->getInfo().getId()) cout << " You found your way, well done!^^ " << endl;

    if (!path[0]->getInfo().getLabel().empty()) cout << " - " << path[0]->getInfo().getLabel();
    cout << endl;
    cout << "The calculated route is " << std::fixed << std::setprecision(2) << cost << " meters long." << endl;
}

void Manager::printOptimalPath(vector<Location> path, double cost) {
    for (int k = 0; k < path.size() - 1; k++)
    {
        cout << path[k].getId();
        if (k % 20 == 0 && k != 0) cout << " .. " << endl << " .. ";
        else cout << " ---> ";
    }
    cout << path[path.size() - 1].getId() << endl;
    if (path[0].getId() == path[path.size()-1].getId()) cout << " You found your way, well done!^^ " << endl;

    if (!path[0].getLabel().empty()) cout << " - " << path[0].getLabel();
    cout << endl;
    cout << "The calculated route is " << std::fixed << std::setprecision(2) << cost << " meters long." << endl;
}

void Manager::clearGraph() {
    int graphSize = graph.getVertexSet().size();
    for (int i = 0; i < graphSize; i++) {
        graph.removeVertex(Location(i));
    }
}
