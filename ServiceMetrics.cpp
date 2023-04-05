//
// Created by anaso on 05/04/2023.
//
#include "ServiceMetrics.h"

ServiceMetrics::ServiceMetrics(){
    this->graph = new Grafo("../stations.csv", "../network.csv");
}

/* [T2.1: 3.5 points] Calculate the maximum number of trains that can simultaneously travel between two specific
 * stations. Note that your implementation should take any valid source and destination stations as input;
 */
int ServiceMetrics::maxNTrainsSimultaneously(std::string origin, std::string destiny){
    return -1;
}


/* [T2.2: 2.0 points] Determine, from all pairs of stations, which ones (if more than one) require the most amount of
 * trains when taking full advantage of the existing network capacity;
 */
std::string ServiceMetrics::pairsRequireMostTrains(){
    return NULL;
}



/* [T2.3: 1.5 points] Indicate where management should assign larger budgets for the purchasing and maintenance of
 * trains. That is, your implementation should be able to report the top-k municipalities and districts, regarding
 * their transportation needs;
 */
std::string ServiceMetrics::largerBudget(){
    return NULL;
}


/* [T2.4: 1 point] Report the maximum number of trains that can simultaneously arrive at a given station, taking into
 * consideration the entire railway grid.
 */
int ServiceMetrics::maxNTrainsArriving(std::string station){
    Vertex* st = graph->findVertexName(station);
    int maxCap = 0;
    for (auto edge:st->getAdj())
        if (edge->getWeight() > maxCap)
            maxCap = int(edge->getWeight());
    return maxCap;
}
