//
// Created by andre on 28/02/2023.
//

#ifndef DA_PROJ1_GRAFO_H
#define DA_PROJ1_GRAFO_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include "VertexEdge.h"

using namespace std;
class Grafo{

public:
    Grafo(std::string stationsFilename, std::string networkFilename);
    ~Grafo();
    Vertex *findVertex(const int &id) const;
    int findVertexIdName(const string &name) const;
    Vertex *findVertexName(const string &name) const;
    bool addVertex(const int &id, string &name, string &district, string &municipality, string &township, string &line);
    bool addEdge(const int &sourc, const int &dest, double w, std::string type);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, std::string type);
    double edmondsKarp(string source, string target);
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    int findVertexIdx(const int &id) const;
    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool findAugmentingPath(Vertex *s, Vertex *t);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //DA_PROJ1_GRAFO_H
