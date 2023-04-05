//
// Created by andre on 07/03/2023.
//
#include <iostream>
#include "ServiceMetrics.h"
#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H
using namespace std;

class Menu {
public:
    Menu();
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
