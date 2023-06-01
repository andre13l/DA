/********************************************************************
 * @file  Grafo.cpp
 *
 * @brief Implementação da classe Grafo
 *********************************************************************/

#include "Grafo.h"

Grafo::Grafo(string nodes, string edges){
    // Create Vertex with nodes.csv file
    string linha, name, longt, lat;
    int i = 0;
    fstream nodesFile (nodes, ios::in);
    if(nodesFile.is_open()) {
        getline(nodesFile, linha);
        while(getline(nodesFile, linha)) {
            stringstream str(linha);
            getline(str, name, ',');
            getline(str, longt, ',');
            getline(str, lat, ',');
            addVertex(i, name, longt, lat);
            i++;
        }
    } else
        cout<<"Could not open the nodes' file\n";
    // Create Edges with edges.csv file
    string origin, destiny, distance;
    fstream edgesFile (edges, ios::in);
    if(edgesFile.is_open()) {
        getline(edgesFile, linha);
        while(getline(edgesFile, linha)) {
            stringstream str(linha);
            getline(str, origin, ',');
            getline(str, destiny, ',');
            getline(str, distance, ',');
            addBidirectionalEdge(findVertexIdName(origin), findVertexIdName(destiny), stod(distance));
        }
    } else
        cout<<"Could not open the edges' file\n";
}

Grafo::Grafo(string database){
    string linha, origin, destiny, distance;

    fstream databaseFile (database, ios::in);
    if(databaseFile.is_open()) {
        getline(databaseFile, linha);
        while(getline(databaseFile, linha)) {
            stringstream str(linha);
            getline(str, origin, ',');
            getline(str, destiny, ',');
            getline(str, distance, ',');
            addBidirectionalEdge(findVertexIdName(origin), findVertexIdName(destiny), stod(distance));
        }
    } else
        cout<<"Could not open the stations' file\n";
}

int Grafo::getNumVertex() const {
    return vertexSet.size();
}

int Grafo::getDists(int v1, int v2) {
    for(auto &e:vertexSet[v1]->getAdj()){
        if(e->getDest()->getId() == v2){
            return e->getDistance();
        }
    }
    return 0;
}

double Grafo::getLati(int v) {
    return stoi(vertexSet[v]->getLatitude());
}

double Grafo::getLongi(int v) {
    return stoi(vertexSet[v]->getLongitude());
}

std::vector<Vertex *> Grafo::getVertexSet() const {
    return vertexSet;
}

Vertex * Grafo::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

int Grafo::findVertexIdName(const string &name) const {
    for (auto v:vertexSet)
        if (v->getName() == name)
            return v->getId();
    return -1;
}

Vertex* Grafo::findVertexName(const string &name) const {
    for (auto v:vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

bool Grafo::addVertex(const int &id, string &name, string &longitude, string &latitude) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, name, longitude, latitude));
    return true;
}


bool Grafo::removeVertex(const string &name) {
    Vertex* v = findVertexName(name);
    if (v == nullptr) {
        return false;
    }

    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        w->removeEdge(v->getId());
        v->removeEdge(w->getId());
    }

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getName() == name){
            vertexSet.erase(it);
            break;
        }
    }

    delete v;
    return true;
}

bool Grafo::addEdge(const int &sourc, const int &dest, double dist) {
    auto v1= findVertex(sourc);
    auto v2= findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, dist);
    return true;
}

bool Grafo::addBidirectionalEdge(const int &sourc, const int &dest, double dist) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, dist);
    auto e2 = v2->addEdge(v1, dist);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void Grafo::testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Grafo::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getDistance() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Grafo::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getDistance() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Grafo::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

double Grafo::edmondsKarp(string source, string target) {
    Vertex* s = findVertexName(source);
    Vertex* t = findVertexName(target);
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // Loop to find augmentation paths and maximumFlow
    double maxFlow = 0;
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        maxFlow += f;
        augmentFlowAlongPath(s, t, f);
    }
    return maxFlow;
}

vector<string> Grafo::getLongitudes() {
    vector<string> municipies = {};
    for(auto i:vertexSet){
        bool isduplicate=false;
        for(auto j:municipies){
            if(i->getLongitude()==j){
                isduplicate= true;
                break;
            }
        }
        if(!isduplicate){
            municipies.push_back(i->getLongitude());
        }
    }
    return municipies;
}

vector<string> Grafo::getLatitudes() {
    vector<string> districts={};
    for(auto i:vertexSet){
        bool isduplicate=false;
        for(auto j:districts){
            if(i->getLatitude()==j){
                isduplicate= true;
                break;
            }
        }
        if(!isduplicate){
            districts.push_back(i->getLatitude());
        }
    }
    return districts;
}

vector<Vertex*> Grafo::getLongtNodes(string &longitude){
    vector<Vertex*>a={};
    for(auto i:vertexSet){
        if(i->getLongitude()==longitude)
            a.push_back(i);
    }
    return a;
}

vector<Vertex*> Grafo::getLatNodes(string &latitude){
    vector<Vertex*>a={};
    for(auto i:vertexSet){
        if(i->getLatitude()==latitude)
            a.push_back(i);
    }
    return a;
}

bool Grafo::findAugmentingPathOptm(Vertex *s, Vertex *t, double c) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getDistance() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Grafo::findMinResidualAlongPathOptm(Vertex *s, Vertex *t, double c) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getDistance() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Grafo::augmentFlowAlongPathOptm(Vertex *s, Vertex *t, double f, double c) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

double Grafo::edmondsKarpOptm(string source, string target) {
    Vertex* s = findVertexName(source);
    Vertex* t = findVertexName(target);
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // Loop to find augmentation paths and maximumFlow
    double maxFlow = 0;
    double minCost = 0;
    double c = 0;
    while( findAugmentingPathOptm(s, t, c) ) {
        double f = findMinResidualAlongPathOptm(s, t, c);
        maxFlow += f;
        //minCost = f*;
        augmentFlowAlongPathOptm(s, t, f, c);
    }
    return minCost;
}

Grafo::~Grafo() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
