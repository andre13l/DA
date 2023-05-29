/*********************************************************************
 * @file  Menu.h
 *
 * @brief Declaração da classe Menu
 *********************************************************************/

#include <iostream>
#include "ServiceMetrics.h"
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
    Menu(ServiceMetrics* servico);
    /**
     * @brief Menu para escolher o tipo de grafo
     **/
    void showinitialMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados de Toy Graphs
     **/
    void showToyGraphMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados de Toy Graphs
     **/
    void showExtraFullyConnectedGraphMenu();
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo sobre a base de dados de Toy Graphs
     **/
    void showRealWorldGraphMenu();
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
     * @brief Método que obtém o ServiceMetric
     * @return Objeto da classe ServiceMetric correspondente
     **/
    ServiceMetrics* getService();
    /**
     * @brief Método que define o service do menu
     * @param service ServiceMetric que o menu vai adotar
     **/
    void setService(ServiceMetrics* service);
protected:
    ServiceMetrics* service;
};


#endif //DA_PROJ1_MENU_H
