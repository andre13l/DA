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

Grafo* ServiceMetrics::createReducedGraph() {
    Grafo* reduced_graph=graph;
    std::string opt = "n";
    bool remove=false;
    while (1){
        std::cout << "\nDo you want to remove a station? (y/N): ";
        cin>>opt;
        if (opt[0] == 'y' || opt[0] == 'Y') {
            remove= true;
            break;
        }
        else if(opt[0] == 'n' || opt[0] == 'N')
            break;
    }

    while (remove) {
        std::cout << "Insert the name of the station you want to remove: \n";
        std::string station_name;
        cin>>station_name;

        while (!(*reduced_graph).removeVertex(station_name)) {
            std::cout << "Invalid station!\n" << "Insert another station name\n";
            cin>>station_name;
        }
        opt = "n";
        std::cout << "Want to remove another station? (y/N): \n";
        cin>>opt;

        if (opt[0] == 'n' || opt[0] == 'N') {
            break;
        }
    }
    return reduced_graph;
}

//TODO
int ServiceMetrics::maxNTrainsReducedConnect() {
    int k;
    string origin;
    string destiny;
    Grafo* gr=createReducedGraph();
    while(1) {
        cout << "Digite o nome da estacao de origem: ";
        cin.ignore();
        getline(cin, origin);
        cout << "\nDigite o nome da estacao de destino: ";
        getline(cin, destiny);
        cout << "\nO numero maximo de comboios que podem viajar simultaneamente entre a estacao " << origin << "e a estacao " << destiny << " sao " << gr->edmondsKarp(origin, destiny) << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        break;
    }

    return int(gr->edmondsKarp(std::move(origin), std::move(destiny)));
}

//TODO
int ServiceMetrics::optimization(std::string origin, std::string destiny){
    return -1;
}
