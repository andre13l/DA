/*********************************************************************
 * @file  ServiceMetrics.h
 *
 * @brief Declaração da classe ServiceMetrics
 *********************************************************************/

#ifndef DA_PROJ1_SERVICEMETRICS_H
#define DA_PROJ1_SERVICEMETRICS_H
#include <string>
#include <algorithm>
#include "Grafo.h"

/**
 * @class ServiceMetrics
 * @brief Classe com os métodos necessários para a resolução do problema inicial
 **/
class ServiceMetrics{
public:
    ServiceMetrics(Grafo* grafo);
    int backtracking(const unsigned int dists, unsigned int n, unsigned int path[]);
    Grafo* getGraph();

protected:
    Grafo* graph;

};

#endif //DA_PROJ1_SERVICEMETRICS_H