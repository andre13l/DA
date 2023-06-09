/*********************************************************************
 * @file  VertexEdge.cpp
 *
 * @brief Implementação das classes Vertex e Edge
 *********************************************************************/

#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line): id(id), name(name), district(district), municipality(municipality), township(township), line(line) {}

Edge * Vertex::addEdge(Vertex *d, double w, std::string type) {
    auto newEdge = new Edge(this, d, w, type);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
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

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

std::string Vertex::getName() const {
    return this->name;
}

std::string Vertex::getDistrict() const{
    return this->district;
}

std::string Vertex::getMunicipality() const{
    return this->municipality;
}

std::string Vertex::getTownship() const{
    return this->township;
}

std::string Vertex::getLine() const{
    return this->line;
}


std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w, std::string type): orig(orig), dest(dest), weight(w), type(type) {
    if (type == "STANDARD")
        cost = 2;
    else if (type == "ALFA PENDULAR")
        cost = 4;
}

Vertex * Edge::getDest() const {
    return this->dest;
}

std::string Edge::getType() const {
    return this->type;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

int Edge::getCost() const {
    return cost;
}


void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

void Edge::setCost(int cost) {
    this->cost = cost;
}
