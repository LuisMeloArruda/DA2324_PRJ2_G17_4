#ifndef DA2324_PRJ2_G17_4_GRAPH_H
#define DA2324_PRJ2_G17_4_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#include <stack>
#include "UFDS.h"

template <class T>
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(T in);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();

    //friend class MutablePriorityQueue<Vertex>;
protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};

/********************** Edge  ****************************/

template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, double w);

    Vertex<T> * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    double getFlow() const;
    double getGradient() const;

    void setWeight(double weight);
    void setSelected(bool selected);
    void setReverse(Edge<T> *reverse);
    void setFlow(double flow);
    void setGradient(double newGradient);
protected:
    Vertex<T> * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;

    double flow; // for flow-related problems
    double gradient; // gradient of the edge
};

/********************** Graph  ****************************/

template <class T>
class Graph {
public:
    ~Graph();
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeEdge(const T &source, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    void setSize(int size);
    std::vector<Vertex<T> *> getVertexSet() const;
    std:: vector<T> dfs() const;
    std:: vector<T> dfs(const T & source) const;
    void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
    std::vector<T> bfs(const T & source) const;
    bool isDAG() const;
    bool dfsIsDAG(Vertex<T> *v) const;
    std::vector<T> topsort() const;

    // auxiliary functions
    /**
     * @brief Computes the Minimum Spanning Tree (MST) of the graph using Kruskal's algorithm.
     *
     * Complexity: O(E log E), where E is the number of edges in the graph.
     *
     */
    void MST();
    /**
     * @brief Finds and returns the vertices with an odd degree.
     *
     * Complexity: O(V), where V is the number of vertices in the graph.
     *
     * @return A vector of pointers to vertices with an odd degree.
     */
    vector<Vertex<T> *> oddVertex();
    /**
     * @brief Sorts edges in ascending order based on their weight.
     *
     * Complexity: O(1)
     *
     * @param first The first edge to compare.
     * @param second The second edge to compare.
     * @return True if the weight of the first edge is less than the weight of the second edge, false otherwise.
     */
    static bool ascending(Edge<T> *first, Edge<T> *second);
    /**
     * @brief Finds the perfect matching for the odd degree vertices and marks the selected edges.
     *
     * Complexity: O(V^2), where V is the number of vertices in the graph.
     *
     * @param odd A vector of pointers to vertices with an odd degree.
     */
    void perfectMatch(const vector<Vertex<T>*>& odd);
    /**
     * @brief Finds and returns an Eulerian tour in the graph.
     *
     * Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
     *
     * @return A stack representing the Eulerian tour.
     */
    stack<Vertex<T> *> eulerianTour();
    /**
     * @brief Auxiliary method to find an Eulerian tour recursively.
     *
     * Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
     *
     * @param vertex The current vertex in the tour.
     * @param tour The stack representing the Eulerian tour.
     */
    void auxEulerianTour(Vertex<T>* vertex, stack<Vertex<T> *> &tour);

protected:
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    int findVertexIdx(const T &in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


/************************* Vertex  **************************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *d, double w) {
    auto newEdge = new Edge<T>(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

template <class T>
bool Vertex<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        Vertex<T> *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

template <class T>
void Vertex<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        delete edge;
    }
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

template <class T>
bool Vertex<T>::isProcessing() const {
    return this->processing;
}

template <class T>
unsigned int Vertex<T>::getIndegree() const {
    return this->indegree;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template <class T>
void Vertex<T>::setInfo(T in) {
    this->info = in;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

template <class T>
void Vertex<T>::setProcesssing(bool processing) {
    this->processing = processing;
}

template <class T>
void Vertex<T>::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

template <class T>
void Vertex<T>::setDist(double dist) {
    this->dist = dist;
}

template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

template <class T>
void Vertex<T>::deleteEdge(Edge<T> *edge) {
    Vertex<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double w): orig(orig), dest(dest), weight(w) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

template <class T>
double Edge<T>::getWeight() const {
    return this->weight;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return this->reverse;
}

template <class T>
bool Edge<T>::isSelected() const {
    return this->selected;
}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

template <class T>
double Edge<T>::getGradient() const {
    return gradient;
}

template <class T>
void Edge<T>::setSelected(bool selected) {
    this->selected = selected;
}

template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}

template <class T>
void Edge<T>::setFlow(double flow) {
    this->flow = flow;
}

template <class T>
void Edge<T>::setWeight(double weight) {
    this->weight = weight;
}

template <class T>
void Edge<T>::setGradient(double newGradient) {
    this->gradient = newGradient;
}


/********************** Graph  ****************************/

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
void Graph<T>::setSize(int size) {
    vertexSet.resize(size, nullptr);
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    return vertexSet[in.getId()];
}

template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet[in.getId()] = new Vertex<T>(in);
    return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T>* v = findVertex(in);
    if (v == nullptr) return false;
    v->removeOutgoingEdges();
    delete v;
    vertexSet[in.getId()] = nullptr;
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** DFS ********************/

template <class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;
    for (auto v : vertexSet)
        v->setVisited(false);
    for (auto v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

template <class T>
std::vector<T> Graph<T>::dfs(const T & source) const {
    std::vector<int> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    // Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/

template <class T>
std::vector<T> Graph<T>::bfs(const T & source) const {
    std::vector<int> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }

    // Perform the actual BFS using a queue
    std::queue<Vertex<T> *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto & e : v->getAdj()) {
            auto w = e->getDest();
            if ( ! w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setProcesssing(false);
    }
    for (auto v : vertexSet) {
        if (! v->isVisited()) {
            if ( ! dfsIsDAG(v) ) return false;
        }
    }
    return true;
}

template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->setVisited(true);
    v->setProcesssing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (! w->isVisited()) {
            if (! dfsIsDAG(w)) return false;
        }
    }
    v->setProcesssing(false);
    return true;
}

/****************** toposort ********************/

template<class T>
std::vector<T> Graph<T>::topsort() const {
    std::vector<int> res;

    for (auto v : vertexSet) {
        v->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    std::queue<Vertex<T> *> q;
    for (auto v : vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while( !q.empty() ) {
        Vertex<T> * v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
        //std::cout << "Impossible topological ordering!" << std::endl;
        res.clear();
        return res;
    }

    return res;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}


// Algoritmos implementados

template <class T>
void Graph<T>::MST() {
    // RESETS THE VISITED FLAG OF VERTICES AND THE SELECTED FLAG OF EDGES IN THE GRAPH
    // PUTS THE EDGES IN A VECTOR
    vector<Edge<T>*> vec;
    for (Vertex<T> *v : vertexSet) {
        v->setVisited(false);
        v->setIndegree(0);
        for (Edge<T> *e : v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getInfo().getId() < e->getDest()->getInfo().getId()) {
                vec.push_back(e);
            }
        }
    }

    // SORTS THE EDGES INSIDE THE VECTOR IN ASCENDING ORDER OF WEIGHT
    std::sort(vec.begin(), vec.end(), Graph<T>::ascending);

    // APPLIES UNION-FIND DATA STRUCTURE ON THE VECTOR TO ASSIGN THE SELECTED ATTRIBUTE TO THE EDGES THAT CAN BE PART OF THE MST
    UFDS ufds(getNumVertex());
    for (Edge<T> *e : vec) {
        if (ufds.findSet(e->getOrig()->getInfo().getId()) != ufds.findSet(e->getDest()->getInfo().getId())) {
            ufds.linkSets(e->getOrig()->getInfo().getId(), e->getDest()->getInfo().getId());
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            Vertex<T>* d = e->getDest();
            Vertex<T>* o = e->getOrig();
            o->setIndegree(o->getIndegree() + 1);
            d->setIndegree(d->getIndegree() + 1);
        }
    }
}

// Christofides

template <class T>
vector<Vertex<T> *> Graph<T>::oddVertex() {
    vector<Vertex<T>*> odd;
    for (Vertex<T> *v  : vertexSet) {
        if (!(v->getIndegree() % 2 == 0)) odd.push_back(v);
    }
    return odd;
}

template <class T>
void Graph<T>::perfectMatch(const vector<Vertex<T>*>& odd) {
    for (auto v: odd) v->setVisited(false);
    vector<Edge<T> *> edges;
    int i = odd.size() - 1;
    // arestas elegíveis
    while (i >= 0) {
        Vertex<T>* v = odd[i];
        for (Edge<T>* e: v->getAdj()) {
            if ((e->getDest()->getIndegree() % 2 != 0) && (e->getOrig()->getInfo().getId() > v->getInfo().getId())) {
                edges.push_back(e);
            }
        }
        i--;
    }
    // ordenar pela distância
    std::sort(edges.begin(), edges.end(), [](Edge<T> *first, Edge<T> *second) {
        return second->getWeight() > first->getWeight();
    });
    // match
    int count = 0;
    for (auto e: edges) {
        if ((!e->getDest()->isVisited() && !e->getOrig()->isVisited())) {
            e->getDest()->setVisited(true);
            e->getOrig()->setVisited(true);

            e->setSelected(true);
            e->getReverse()->setSelected(true);
            count++; count++;
        }
        if (count == odd.size()) return;
    }
}

template <class T>
stack<Vertex<T> *> Graph<T>::eulerianTour() {
    for (Vertex<T> *v : vertexSet) {
        for (Edge<T>* e: v->getAdj()) {
            e->setSelected(false);
            e->getReverse()->setSelected(false);
        }
    }
    stack<Vertex<T> *> tour;
    auxEulerianTour(vertexSet[0], tour);
    return tour;
}

template <class T>
void Graph<T>::auxEulerianTour(Vertex<T>* vertex, stack<Vertex<T> *> &tour) {
    for (Edge<T>* e: vertex->getAdj()) {
        if (!e->isSelected()) {
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            auxEulerianTour(e->getDest(), tour);
        }
    }
    tour.push(vertex);
}

template <class T>
bool Graph<T>::ascending(Edge<T> *first, Edge<T> *second) {
    return first->getWeight() < second->getWeight();
}
#endif //DA2324_PRJ2_G17_4_GRAPH_H
