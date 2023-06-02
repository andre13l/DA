/********************************************************************
 * @file  Grafo.cpp
 *
 * @brief Implementação da classe Grafo
 *********************************************************************/

#include "Grafo.h"

Grafo::Grafo(string nodes, string edges){
    // Create Vertex with nodes.csv file
    string linha, name, longt, lat;
    fstream nodesFile (nodes, ios::in);
    if(nodesFile.is_open()) {
        getline(nodesFile, linha);
        while(getline(nodesFile, linha)) {
            stringstream str(linha);
            getline(str, name, ',');
            getline(str, longt, ',');
            getline(str, lat, ',');
            addVertex(stoi(name), name, longt, lat);
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
            addEdge(findVertexIdName(origin), findVertexIdName(destiny), stod(distance));
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
            addVertex(stoi(origin), origin);
            addVertex(stoi(destiny), destiny);
            addEdge(findVertexIdName(origin), findVertexIdName(destiny), stod(distance));
        }
    } else
        cout<<"Could not open the database's file\n";
}

int Grafo::getNumVertex() const {
    return vertexSet.size();
}

double** Grafo::getDists() {
    int n = getNumVertex();
    double **dists = new double *[n];
    for (int i = 0; i < n; ++i) {
        dists[i] = new double[n];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bool ti = false;
            if(i==j){
                dists[i][j]=0;
            }
            else if(!ti){
                dists[i][j]=-1;
            }
            for(auto &e:vertexSet[i]->getAdj()){
                if(e->getDest()->getId() == j){
                    dists[i][j]= e->getDistance();
                    ti = true;
                }
            }
        }
    }
    return dists;
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

bool Grafo::addVertex(const int &id, const string &name) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, name, "0", "0"));
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

void Grafo::tspBTRec(double **dists, unsigned int n, unsigned int curIndex, double curDist, unsigned int curPath[], double &minDist, unsigned int path[]) {
    if(curIndex == n) {
        // add the distance back to the initial node
        curDist += dists[curPath[n - 1]][curPath[0]];
        if (curDist < minDist) {
            cout << "inside if curDist < minDist; curDist=" << curDist << ", minDist=" << minDist << endl;
            minDist = curDist;
            // Copy the current state to the array storing the best state found so far
            for (unsigned int i = 0; i < n; i++) {
                path[i] = curPath[i];
            }
        }
        return;
    }
    // Try to move to the i-th vertex if the total distance does not exceed the best distance found and the vertex is not yet visited in curPath
    for(unsigned int i = 1; i < n; i++) { // i starts at 1 and not 0 since it is assumed that node 0 is the initial node so it will not be in the middle of the path
        if(curDist + dists[curPath[curIndex - 1]][i] < minDist) {
            bool isNewVertex = true;
            for(unsigned int j = 1; j < curIndex; j++) {
                if(curPath[j] == i) {
                    isNewVertex = false;
                    break;
                }
            }
            if(isNewVertex) {
                curPath[curIndex] = i;
                tspBTRec(dists,n,curIndex+1,curDist + dists[curPath[curIndex - 1]][curPath[curIndex]],curPath,minDist,path);
            }
        }
    }
}

double Grafo::backtracking(double **dists, unsigned int n, unsigned int *path) {
    unsigned int curPath[10000]; // static memory allocation is faster :)
    double minDist = std::numeric_limits<double>::max();

    // Assumes path starts at node 0 ...
    curPath[0] = 0;
    // ... so in the first recursive call curIndex starts at 1 rather than 0
    tspBTRec(dists, n, 1, 0, curPath, minDist, path);
    return minDist;
}

Grafo::~Grafo() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
