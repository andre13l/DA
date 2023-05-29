/********************************************************************
 * @file  Grafo.cpp
 *
 * @brief Implementação da classe Grafo
 *********************************************************************/

#include "Grafo.h"

Grafo::Grafo(string nodes, string edges){
    // Create Vertex with stations.csv file
    string linha, name, district, municipality, township, line;
    int i = 0;
    fstream stationsFile (nodes, ios::in);
    if(stationsFile.is_open()) {
        getline(stationsFile, linha);
        while(getline(stationsFile, linha)) {
            stringstream str(linha);
            getline(str, name, ',');
            getline(str, district, ',');
            getline(str, municipality, ',');
            getline(str, township, ',');
            getline(str, line, ',');
            addVertex(i, name, district, municipality, township, line);
            i++;
        }
    } else
        cout<<"Could not open the stations' file\n";
    // Create Edges with network.csv file
    string origin, destiny, weight, type;
    fstream networkFile (edges, ios::in);
    if(networkFile.is_open()) {
        getline(networkFile, linha);
        while(getline(networkFile, linha)) {
            stringstream str(linha);
            getline(str, origin, ',');
            getline(str, destiny, ',');
            getline(str, weight, ',');
            getline(str, type, ',');
            addBidirectionalEdge(findVertexIdName(origin), findVertexIdName(destiny), stod(weight), type);
        }
    } else
        cout<<"Could not open the network's file\n";
}

Grafo::Grafo(string database){
    string linha, name, district, municipality, township, line;
    int i = 0;
    fstream stationsFile (database, ios::in);
    if(stationsFile.is_open()) {
        getline(stationsFile, linha);
        while(getline(stationsFile, linha)) {
            stringstream str(linha);
            getline(str, name, ',');
            getline(str, district, ',');
            getline(str, municipality, ',');
            getline(str, township, ',');
            getline(str, line, ',');
            addVertex(i, name, district, municipality, township, line);
            i++;
        }
    } else
        cout<<"Could not open the stations' file\n";
}

int Grafo::getNumVertex() const {
    return vertexSet.size();
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

bool Grafo::addVertex(const int &id, string &name, string &district, string &municipality, string &township, string &line) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, name, district, municipality, township, line));
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

bool Grafo::addEdge(const int &sourc, const int &dest, double w, string type) {
    auto v1= findVertex(sourc);
    auto v2= findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, type);
    return true;
}

bool Grafo::addBidirectionalEdge(const int &sourc, const int &dest, double w, string type) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, type);
    auto e2 = v2->addEdge(v1, w, type);
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
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
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
            f = std::min(f, e->getWeight() - e->getFlow());
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

vector<string> Grafo::getMunicipies(){
    vector<string> municipies = {};
    for(auto i:vertexSet){
        bool isduplicate=false;
        for(auto j:municipies){
            if(i->getMunicipality()==j){
                isduplicate= true;
                break;
            }
        }
        if(!isduplicate){
            municipies.push_back(i->getMunicipality());
        }
    }
    return municipies;
}

vector<string> Grafo::getDistricts(){
    vector<string> districts={};
    for(auto i:vertexSet){
        bool isduplicate=false;
        for(auto j:districts){
            if(i->getDistrict()==j){
                isduplicate= true;
                break;
            }
        }
        if(!isduplicate){
            districts.push_back(i->getMunicipality());
        }
    }
    return districts;
}

vector<Vertex*> Grafo::getMunStations(string &municipy){
    vector<Vertex*>a={};
    for(auto i:vertexSet){
        if(i->getMunicipality()==municipy)
            a.push_back(i);
    }
    return a;
}

vector<Vertex*> Grafo::getDistStations(string &district){
    vector<Vertex*>a={};
    for(auto i:vertexSet){
        if(i->getDistrict()==district)
            a.push_back(i);
    }
    return a;
}

int Grafo::findMunCapacity(string &municipy){
    int cap=0;
    vector<Vertex*>a = getMunStations(municipy);
    for(int i=0;i<a.size();i++){
        for(auto j:a[i]->getAdj()){
            cap+=j->getWeight();
        }
    }
    return cap;
}

int Grafo::findDisCapacity(string &district){
    int cap=0;
    vector<Vertex*>a = getDistStations(district);
    for(int i=0;i<a.size();i++){
        for(auto j:a[i]->getAdj()){
            cap+=j->getWeight();
        }
    }
    return cap;
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
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
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
            f = std::min(f, e->getWeight() - e->getFlow());
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
