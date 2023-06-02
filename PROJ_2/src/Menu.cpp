/*********************************************************************
 * @file  Menu.cpp
 *
 * @brief Implementação da classe Menu
 *********************************************************************/


#include "Menu.h"
Menu::Menu(){}

Menu::Menu(Grafo* grafo): graph(grafo) {}

void Menu::setGraph(Grafo* graph){
    this->graph = graph;
}

Grafo* Menu::getGraph() {
    return graph;
}

void Menu::showinitialMenu(){
    int k;
    while(1) {
        cout << "Escolha os documentos para inicializar: " << endl;
        cout << "Escolha uma opcao de 1 a 4 ou 0 para sair:"<< endl;
        cout << "1  -- Toy Graphs" << endl;
        cout << "2  -- Extra Fully Connected Graphs" << endl;
        cout << "3  -- Real-World Graphs" << endl;
        cout << "4  -- Other Graph" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2|| k == 3 || k == 4)){
            cout << "Introduza um dos valores pedidos (1 a 4 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1:showToyGraphMenu(); break;
            case 2:showExtraFullyConnectedGraphMenu(); break;
            case 3:showRealWorldGraphMenu(); break;
            case 4:showOtherGraph(); break;
            case 0: return;
        }
        cout << "0  -- Sair" << endl;
        cin >> k;
    }
}


void Menu::showToyGraphMenu(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 3 ou 0 para sair:"<< endl;
        cout << "1  -- Shipping" << endl;
        cout << "2  -- Stadiums" << endl;
        cout << "3  -- Tourism" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2 || k==3)){
            cout << "Introduza um dos valores pedidos (1 a 3 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1: {
                auto* grafo = new Grafo("../../dataset/Toy-Graphs/shipping.csv");
                setGraph(grafo);

                /*cout << "TOY GRAPH WORKING: " << endl;
                for (int i = 0; i < getGraph()->getNumVertex(); i++){
                    cout << "vertex id = " << getGraph()->getVertexSet()[i]->getId() << endl;
                }*/

                showHeuristic(); break;
            }
            case 2:{
                auto* grafo = new Grafo("../../dataset/Toy-Graphs/stadiums.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 3:{
                auto* grafo = new Grafo("../../dataset/Toy-Graphs/tourism.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 0: return;
        }
    }
}

void Menu::showExtraFullyConnectedGraphMenu(){
    int k;
    while(1) {
        cout << "Escolha a quantidade de nós do grafo (25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800 ou 900) ou 0 para sair:"<< endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k==25 || k==50 || k==75 || k==100 || k==200 || k==300 || k==400 || k==500 || k==600 || k==700 || k==800 || k==900)){
            cout << "Introduza um dos valores pedidos (ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 25: {
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_25.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 50:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 75:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_75.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 100:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_100.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 200:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_200.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 300:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_300.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 400:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_400.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 500:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_500.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 600:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_600.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 700:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_700.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 800:{
                auto* grafo = new Grafo("../../dataset/Extra_Fully_Connected_Graphs/edges_800.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 0: return;
        }
    }
}
void Menu::showRealWorldGraphMenu(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 3 ou 0 para sair:"<< endl;
        cout << "1  -- Grafo 1" << endl;
        cout << "2  -- Grafo 2" << endl;
        cout << "3  -- Grafo 3" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2 || k==3)){
            cout << "Introduza um dos valores pedidos (1 a 3 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1: {
                auto* grafo = new Grafo("../../dataset/Real-world_Graphs/graph1/nodes.csv", "../dataset/Real-world_Graphs/graph1/edges.csv");
                setGraph(grafo);

                /*cout << "REAL WORLD GRAPHS WORKING: " << endl;
                for (int i = 0; i < 20; i++){
                    cout << "vertex id = " << getGraph()->getVertexSet()[i]->getId() << endl;
                }*/

                showHeuristic(); break;
            }
            case 2:{
                auto* grafo = new Grafo("../../dataset/Real-world_Graphs/graph2/nodes.csv", "../dataset/Real-world_Graphs/graph2/edges.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 3:{
                auto* grafo = new Grafo("../../dataset/Real-world_Graphs/graph3/nodes.csv", "../dataset/Real-world_Graphs/graph3/edges.csv");
                setGraph(grafo);

                showHeuristic(); break;
            }
            case 0: return;
        }
    }
}

void Menu::showOtherGraph() {
    std::string database;
    cout << "Digite o nome do documento para inicializar o grafo: " << endl;
    cin >> database;
    auto* grafo = new Grafo("../../dataset/" + database);
    setGraph(grafo);
    showHeuristic();
}

void Menu::showHeuristic(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 3 ou 0 para sair:"<< endl;
        cout << "1  -- Algoritmo de Backtracking" << endl;
        cout << "2  -- Triangular Approximation Heuristic" << endl;
        cout << "3  -- Outras Heuristicas" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2 || k==3)){
            cout << "Introduza um dos valores pedidos (1 a 3 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1:showBacktrack(); break;
            case 2:showTriApprox(); break;
            case 3:showOther();break;
            case 0: return;
        }
    }
}

void Menu::showBacktrack(){
    int k;
    while(1) {
        int n = getGraph()->getNumVertex();
        unsigned int* v;
        cout << "Backtracking: " << getGraph()->backtracking(getGraph()->getDists(), n, v) << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        return;
    }
}

void Menu::showTriApprox() {
    int k;
    std::string origin, destiny;
    while(1) {
        cout << "Em construcao... " << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        return;
    }
}

void Menu::showOther(){
    int k;
    std::string origin, destiny;
    while(1) {
        cout << "Em construcao..." << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        return;
    }
}
