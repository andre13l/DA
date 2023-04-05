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
    void showinitialMenu();
    void showMenu();
    void showOptimization();
    void showBasic();
    void showReliability();

    void showMaxNTrainsSimultaneously();
    void showPairsRequiredMostTrains();
    void showLargerBudget();
    void showMaxNTrainsArriving();

    ServiceMetrics* getService();
    void setService(ServiceMetrics* service);
protected:
    ServiceMetrics* service;
};


#endif //DA_PROJ1_MENU_H
