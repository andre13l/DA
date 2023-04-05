//
// Created by anaso on 05/04/2023.
//

#ifndef DA_PROJ1_SERVICEMETRICS_H
#define DA_PROJ1_SERVICEMETRICS_H
#include <string>
#include "Grafo.h"

class ServiceMetrics{
public:
    ServiceMetrics();
    ServiceMetrics(Grafo* grafo);
    int maxNTrainsSimultaneously(std::string origin, std::string destiny);
    std::string pairsRequireMostTrains();
    std::string largerBudget();
    int maxNTrainsArriving(std::string station);
protected:
    Grafo* graph;
};

#endif //DA_PROJ1_SERVICEMETRICS_H
