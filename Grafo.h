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
    Grafo(std::string stationsFilename, std::string networkFilename);
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
    Vertex *findVertexName(const string &name) const;

    /**
     * @brief Método que adiciona um vértice ao grafo
     * @param id id do vértice
     * @param name Nome do vértice
     * @param district Nome do distrito do vértice
     * @param municipality Nome do município do vértice
     * @param township Nome da freguesia do vértice
     * @param line Nome da Linha do vértice
     * @retval true Se o vértice foi adicionado corretamente
     * @retval false Se o vértice não foi adicionado
     **/
    bool addVertex(const int &id, string &name, string &district, string &municipality, string &township, string &line);

    /**
     * @brief Método que adiciona uma aresta ao grafo
     * @param sourc Índice do vértice de origem
     * @param dest Índice do vértice de destino
     * @param w Peso da aresta
     * @param type Tipo referente à aresta
     * @retval true Se a aresta foi adicionada corretamente
     * @retval false Se a aresta não foi adicionada
     **/
    bool addEdge(const int &sourc, const int &dest, double w, std::string type);

    /**
     * @brief Método que adiciona uma aresta bidirecional ao grafo
     * @param sourc Índice do vértice de origem
     * @param dest Índice do vértice de destino
     * @param w Peso da aresta
     * @param type Tipo referente à aresta
     * @retval true Se a aresta foi adicionada corretamente
     * @retval false Se a aresta não foi adicionada
     **/
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, std::string type);

    /**
     * @brief Método que utiliza o método de Edmonds-Karp para encontrar os augmentation paths e o fluxo máximo
     * @param source Nome do vértice de origem
     * @param target Nome do vértice de destino
     * @return O fluxo máximo
     **/
    double edmondsKarp(string source, string target);

    /**
     * @brief Método que obtém o número de vértices do grafo
     * @return O número de vértices existente no grafo
     **/
    int getNumVertex() const;

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
    /**
     * @brief Método para descobrir o Augmenting Path
     * @param s Vértice de origem
     * @param t Vértice de destino
     * @retval true Quando o vértice de destino é visitado
     * @retval false Quando o vértice de destino ainda não foi visitado
     **/
    bool findAugmentingPath(Vertex *s, Vertex *t);
    /**
     * @brief Método para descobrir o fluxo residual mínimo
     * @param s Vértice de origem
     * @param t Vértice de destino
     * @return Número do fluxo residual mínimo
     **/
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    /**
     * @brief Método para definir o fluxo residual ao longo do algoritmo
     * @param s Vértice de origem
     * @param t Vértice de destino
     * @param f Fluxo residual
     **/
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //DA_PROJ1_GRAFO_H
