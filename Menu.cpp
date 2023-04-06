/*********************************************************************
 * @file  Menu.cpp
 *
 * @brief Implementação da classe Menu
 *********************************************************************/


#include "Menu.h"

Menu::Menu(){
    service = new ServiceMetrics();
}

Menu::Menu(ServiceMetrics* servico): service(servico) {}

void Menu::setService(ServiceMetrics* service){
    this->service = service;
}

ServiceMetrics* Menu::getService() {
    return service;
}

void Menu::showinitialMenu(){
    int k;
    while(1) {
        cout << "Escolha os documentos para inicializar a rede ferroviaria: " << endl;
        cout << "Escolha uma opcao de 1 a 2 ou 0 para sair:"<< endl;
        cout << "1  -- Documentos padrao (network.csv e stations.csv)" << endl;
        cout << "2  -- Outros documentos" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2)){
            cout << "Introduza um dos valores pedidos (1 a 2 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1:showMenu(); break;
            case 2:{
                std::string network, stations;
                cout << "Digite o nome do documento para inicializar as estacoes: " << endl;
                cin >> stations;
                cout << "Digite o nome do documento para inicializar a rede: " << endl;
                cin >> network;
                auto* grafo = new Grafo(stations, network);
                auto* servico = new ServiceMetrics(grafo);
                setService(servico);
                showMenu(); break;
            }
            case 0: return;
        }
        cout << "Escolha os documentos para inicializar a rede ferroviaria: " << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
    }
}

void Menu::showMenu(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 3 ou 0 para sair:"<< endl;
        cout << "1  -- Métricas Basicas de Servico" << endl;
        cout << "2  -- Otimizacao" << endl;
        cout << "3  -- Confiabilidade e Sensibilidade a Falhas na Linha" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2 || k==3)){
            cout << "Introduza um dos valores pedidos (1 a 3 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1:showBasic(); break;
            case 2:showOptimization(); break;
            case 3:showReliability();break;
            case 0: return;
        }
    }
}
void Menu::showBasic(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 4 ou 0 para sair:"<< endl;
        cout << "1  -- Numero maximo de comboios que podem viajar entre duas estacoes" << endl;
        cout << "2  -- Pares de estacoes que requerem a maior quantidade de comboios" << endl;
        cout << "3  -- Onde a administracao deve atribuir orcamentos maiores para a compra e manutenção de comboios" << endl;
        cout << "4  -- Numero maximo de comboios que podem chegar simultaneamente a uma dada estacao" << endl;
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2 || k==3 || k==4)){
            cout << "Introduza um dos valores pedidos (1 a 4 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            case 1:showMaxNTrainsSimultaneously(); break;
            case 2:showPairsRequiredMostTrains(); break;
            case 3:showLargerBudget();break;
            case 4:showMaxNTrainsArriving();break;
            case 0: return;
        }
    }
}
void Menu::showOptimization() {
    int k=1;
    cin >> k;
    while(k!=0){
        cout << "Pressione 0 para sair" << endl;
        cin >> k;
    }
}
void Menu::showReliability(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 2 ou 0 para sair "<< endl;
        cout << "1  -- Calcular o numero maximo de comboios que podem viajar entre duas estacoes especificas numa rede de conectividade reduzida" << endl;
        cout << "2  -- Relatorio sobre as estacoes mais afetadas por cada falha de segmento" << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2)){
            cout << "Introduza um dos valores pedidos (1 a 2 , ou 0 caso pretenda sair)" << endl;
            cin >> k;
        }
        switch (k) {
            /*case 1:showBasic(); break;
            case 2:showOptimization(); break;
            case 3:showReliability();break;*/
            case 0: return;
        }
    }
}


void Menu::showMaxNTrainsSimultaneously(){
    int k;
    std::string origin, destiny;
    while(1) {
        cout << "Digite o nome da estacao de origem: ";
        cin.ignore();
        getline(cin, origin);
        cout << "\nDigite o nome da estacao de destino: ";
        getline(cin, destiny);
        cout << "\nO numero maximo de comboios que podem viajar simultaneamente entre a estacao " << origin << "e a estacao " << destiny << " sao " << service->maxNTrainsSimultaneously(origin, destiny) << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        return;
    }
}


void Menu::showPairsRequiredMostTrains(){
    vector<string> pairs = service->pairsRequireMostTrains();
    int k;
    while(1) {
        cout << "Os pares de estacoes que requerem mais comboios para aproveitar o maximo de capacidade da rede existente tem a capacidade de " << pairs[0] << " e sao os seguintes:" << endl;
        for (int i=1; i < pairs.size(); i++){
            cout << pairs[i] << endl;
        }
        cout << "0  -- Sair" << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair)" << endl;
            cin >> k;
        }
        return;
    }
}


//TODO
void Menu::showLargerBudget(){
    int k, q;
    while(1) {
        cout << "Escolha a quantidade de estacoes que pretende visualizar"<< endl;
        cin >> q;
        cout << "O top-" << q << " de municipios e distritos que a administracao deve destinar maiores orcamentos para a compra e manutencao de comboios sao:" << endl;
        for (int i=0; i<q; i++){
            cout << service->largerBudget()[i] << endl;
        }
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        return;
    }
}

void Menu::showMaxNTrainsArriving(){
    int k;
    while(1) {
        std::string station;
        cout << "Digite o nome da estacao pretendida: ";
        cin.ignore();
        getline(cin, station);
        cout << "\nA Estacao " << station << " tem uma capacidade maxima de receber " << service->maxNTrainsArriving(station) << " comboios simultaneamente" << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(k!=0){
            cout << "Introduza 0 para sair" << endl;
            cin >> k;
        }
        return;
    }
}
