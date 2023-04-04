//
// Created by andre on 28/02/2023.
//
#include "Grafo.h"

Grafo::Grafo(string filename){
    vector<vector<string>> content;
    vector<string> row;
    string linha, name, district, municipality, township, line;
    int i = 0;
    fstream file (filename, ios::in);
    if(file.is_open()) {
        while(getline(file, linha)) {
            row.clear();
            stringstream str(linha);
            getline(str, name, ',');
            getline(str, district, ',');
            getline(str, municipality, ',');
            getline(str, township, ',');
            getline(str, line, ',');
            addVertex(i, name, district, municipality, township, line);
            i++;
        }
        cout << "Number of vertex - " << getNumVertex();
    } else
        cout<<"Could not open the file\n";
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

int Grafo::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
bool Grafo::addVertex(const int &id, string &name, string &district, string &municipality, string &township, string &line) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, name, district, municipality, township, line));
    return true;
}

bool Grafo::addEdge(const int &sourc, const int &dest, double w) {
    auto v1= findVertex(sourc);
    auto v2= findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Grafo::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
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

Grafo::~Grafo() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
