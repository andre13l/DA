//
// Created by andre on 28/02/2023.
//

#ifndef DA_PROJ1_GRAFO_H
#define DA_PROJ1_GRAFO_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "./VertexEdge.h"

using namespace std;
class Grafo{

public:
    Grafo(std::string stationsFilename, std::string networkFilename);
    ~Grafo();
    Vertex *findVertex(const int &id) const;
    int findVertexName(const string &name) const;
    bool addVertex(const int &id, string &name, string &district, string &municipality, string &township, string &line);
    bool addEdge(const int &sourc, const int &dest, double w, std::string type);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, std::string type);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    int findVertexIdx(const int &id) const;

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //DA_PROJ1_GRAFO_H
