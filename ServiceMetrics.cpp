/*********************************************************************
 * @file  ServiceMetrics.cpp
 *
 * @brief Implementação da classe ServiceMetrics
 *********************************************************************/


#include "ServiceMetrics.h"

#include <utility>

ServiceMetrics::ServiceMetrics(){
    this->graph = new Grafo("../stations.csv", "../network.csv");
}

ServiceMetrics::ServiceMetrics(Grafo* grafo): graph(grafo){}


int ServiceMetrics::maxNTrainsSimultaneously(std::string origin, std::string destiny){
    return graph->edmondsKarp(std::move(origin), std::move(destiny));
}

std::string ServiceMetrics::pairsRequireMostTrains(){
    return NULL;
}

std::string ServiceMetrics::largerBudget(){
    return NULL;
}

int ServiceMetrics::maxNTrainsArriving(std::string station){
    Vertex* st = graph->findVertexName(station);
    int maxCap = 0;
    for (auto edge:st->getAdj())
        if (edge->getWeight() > maxCap)
            maxCap = int(edge->getWeight());
    return maxCap;
}
