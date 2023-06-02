/*********************************************************************
 * @file  Grafo.h
 *
 * @brief Declaração da classe Grafo
 *********************************************************************/

#ifndef DA_PROJ1_GRAFO_H
#define DA_PROJ1_GRAFO_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include "VertexEdge.h"

using namespace std;

/**
 * @class Grafo
 * @brief Classe relativa ao grafo
 * **/
class Grafo{

public:
    Grafo(std::string nodesFilename, std::string edgesFilename);
    Grafo(std::string databaseFilename);
    ~Grafo();
    /**
     * @brief Método que encontra o vértice a partir do índice
     * @param id Id do vértice
     * @return Índice correspondente ao nome do vértice
     **/
    Vertex *findVertex(const int &id) const;

    /**
     * @brief Método que encontra o índice do vértice a partir do seu nome
     * @param name Nome do vértice
     * @return Índice correspondente ao nome do vértice
     **/
    int findVertexIdName(const string &name) const;

    /**
     * @brief Método que encontra o vértice a partir do seu nome
     * @param name Nome do vértice
     * @return Vértice correspondente ao nome do vértice
     **/
    Vertex* findVertexName(const string &name) const;

    /**
     * @brief Método que adiciona um vértice ao grafo
     * @param id id do vértice
     * @param name Nome do vértice
     * @param longitude Longitude do vértice
     * @param latitude Latitude do vértice
     * @retval true Se o vértice foi adicionado corretamente
     * @retval false Se o vértice não foi adicionado
     **/
    bool addVertex(const int &id, string &name, string &longitude, string &latitude);

    /**
     * @brief Método que adiciona um vértice ao grafo
     * @param id id do vértice
     * @param name Nome do vértice
     * @retval true Se o vértice foi adicionado corretamente
     * @retval false Se o vértice não foi adicionado
     **/
    bool addVertex(const int &id, const string &name);

    /**
     * @brief Remove a vertex from the graph
     * @param name nome do vértice
     * @return true Se o vértice foi removido corretamente
     * @retval false Se o vértice não foi removido
     */
    bool removeVertex(const string &id);

    /**
     * @brief Método que adiciona uma aresta ao grafo
     * @param sourc Índice do vértice de origem
     * @param dest Índice do vértice de destino
     * @param dist Peso da aresta
     * @retval true Se a aresta foi adicionada corretamente
     * @retval false Se a aresta não foi adicionada
     **/
    bool addEdge(const int &sourc, const int &dest, double dist);

    /**
     * @brief Método que adiciona uma aresta bidirecional ao grafo
     * @param sourc Índice do vértice de origem
     * @param dest Índice do vértice de destino
     * @param dist Peso da aresta
     * @retval true Se a aresta foi adicionada corretamente
     * @retval false Se a aresta não foi adicionada
     **/
    bool addBidirectionalEdge(const int &sourc, const int &dest, double dist);

    /**
     * @brief Método que obtém o número de vértices do grafo
     * @return O número de vértices existente no grafo
     **/
    int getNumVertex() const;

    /**
     * @brief Método que obtém as distâncias que um vértice tem aos outros do grafo
     * @return Um vetor com as distâncias que um vértice tem aos outros do grafo
     **/
    double** getDists();

    void tspBTRec(double **dists, unsigned int n, unsigned int curIndex, double curDist, unsigned int curPath[], double &minDist, unsigned int path[]);
    double backtracking(double **dists, unsigned int n, unsigned int path[]);
    /**
     * @brief Método que obtém os vértices do grafo
     * @return Um vetor com os vértices do grafo
     **/
    std::vector<Vertex *> getVertexSet() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /**
     * @brief Método para marcar o vértice como visitado
     * @param q Queue de vértices
     * @param e Aresta
     * @param w Vértice
     * @param residual Fluxo Residual
     **/
    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //DA_PROJ1_GRAFO_H