//
// Created by andre on 07/03/2023.
//

#include "Menu.h"
void Menu::showMenu(){
    int k;
    while(1) {
        cout << "Escolha uma opcao de 1 a 3 ou 0 para sair "<< endl;
        cout << "1  -- Basic Service Metrics " << endl;
        cout << "2  -- Optimization " << endl;
        cout << "3  -- Reliability and Sensitivity to Line Failures  " << endl;
        cout << "0  -- Sair " << endl;
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
        cout << "Escolha uma opcao de 1 a 4 ou 0 para sair "<< endl;
        cout << "1  -- Maximum number of trains that can travel between 2 stations " << endl;
        cout << "2  -- Pair of stations that require the most amount of trains " << endl;
        cout << "3  -- Indicate where management should assign larger budgets for the purchasing and maintenance of trains  " << endl;
        cout << "4  -- Maximum number of trains that can simultaneously arrive at a given station  " << endl;
        cout << "0  -- Sair " << endl;
        cin >> k;
        while(!(k==0 || k == 1 || k == 2 || k==3)){
            cout << "Introduza um dos valores pedidos (1 a 3 , ou 0 caso pretenda sair)" << endl;
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
        cout << "1  -- Calculate the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity " << endl;
        cout << "2  -- Provide a report on the stations that are the most affected by each segment failure " << endl;
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
