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
    return int(graph->edmondsKarp(std::move(origin), std::move(destiny)));
}

std::vector<std::string> ServiceMetrics::pairsRequireMostTrains(){
    double max=0;
    vector<string> pairs;
    for (int i = 0; i < graph->getVertexSet().size(); i++){
        for (int j = 0; j < graph->getVertexSet()[i]->getIncoming().size(); j++){
            if (graph->getVertexSet()[i]->getIncoming()[j]->getWeight() > max){
                max = graph->getVertexSet()[i]->getIncoming()[j]->getWeight();
            }
        }
    }
    pairs.push_back(to_string(int(max)));
    std::ostringstream p;
    for (int k = 0; k < graph->getVertexSet().size(); k++){
        for (int l = 0; l < graph->getVertexSet()[k]->getIncoming().size(); l++){
            if (graph->getVertexSet()[k]->getIncoming()[l]->getWeight() == max){
                Edge* edgeWith10 = graph->getVertexSet()[k]->getIncoming()[l];
                p << edgeWith10->getOrig()->getName() << " -----> " << edgeWith10->getDest()->getName();
                std::string pair = p.str();
                pairs.push_back(pair);
                p.str("");
                p.clear();
            }
        }
    }
    return pairs;
}

//TODO
bool cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second; // Sort in ascending order based on the int value
}

std::vector<pair<string,string>> ServiceMetrics::largerBudget(){
    int maxcap;
    vector<pair<string,int>> mun;
    vector<pair<string,int>> dist;
    vector<pair<string,string>> solution;
    for(auto i:graph->getMunicipies()){
        maxcap=graph->findMunCapacity(i);
        mun.push_back(make_pair(i,maxcap));
    }
    sort(mun.begin(),mun.end(),cmp);
    for(auto i:graph->getDistricts()){
        maxcap=graph->findDisCapacity(i);
        dist.push_back(make_pair(i,maxcap));
    }
    sort(dist.begin(),dist.end(),cmp);
    for(int i=0;i<dist.size();i++){
        solution.push_back(make_pair(mun[i].first,dist[i].first));
    }

    return solution;
}

int ServiceMetrics::maxNTrainsArriving(std::string station){
    Vertex* st = graph->findVertexName(station);
    int maxCap = 0;
    for (auto edge:st->getAdj())
        if (edge->getWeight() > maxCap)
            maxCap = int(edge->getWeight());
    return maxCap;
}

//TODO
int ServiceMetrics::optimization(std::string origin, std::string destiny){
    return -1;
}
