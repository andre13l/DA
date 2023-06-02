/*********************************************************************
 * @file  Menu.h
 *
 * @brief Declaração da classe Menu
 *********************************************************************/

#include <iostream>
#include "Grafo.h"
#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H
using namespace std;

/**
 * @class Menu
 * @brief Classe relativa ao menu
 * **/
class Menu {
public:
    Menu();
    Menu(Grafo* graph);
    /**
     * @brief Menu para escolher o tipo de grafo
     **/
    void showinitialMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados de Toy Graphs
     **/
    void showToyGraphMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados de Extra Fully Connected
     **/
    void showExtraFullyConnectedGraphMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados de Real World
     **/
    void showRealWorldGraphMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados extra
     **/
    void showOtherGraph();
    /**
     * @brief Menu principal para escolher entre as heurísticas
     **/
    void showHeuristic();
    /**
     * @brief Menu relativo à heurística de Backtracking
     **/
    void showBacktrack();
    /**
     * @brief Menu relativo à heurística de Triangular Approximation
     **/
    void showTriApprox();
    /**
     * @brief Menu relativo a outras heurísticas
     **/
    void showOther();
    /**
     * @brief Método que obtém o Grafo
     * @return Objeto da classe Grafo correspondente
     **/
    Grafo* getGraph();
    /**
     * @brief Método que define o grafo do menu
     * @param graph Grafo que o menu vai adotar
     **/
    void setGraph(Grafo* graph);
protected:
    Grafo* graph;
};


#endif //DA_PROJ1_MENU_H
