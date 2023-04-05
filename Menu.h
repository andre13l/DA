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
    /**
     * @brief Menu para escolher os ficheiros que vão construir o grafo
     **/
    void showinitialMenu();
    /**
     * @brief Menu principal para escolher entre serviços básicos de métrica, otimização ou confiabilidade e sensibilidade a falhas na linha
     **/
    void showMenu();
    /**
     * @brief Menu relativo à otimização
     **/
    void showOptimization();
    /**
     * @brief Menu relativo aos serviços básicos de métrica
     **/
    void showBasic();
    /**
     * @brief Menu relativo à confiabilidade e sensibilidade a falhas na linha
     **/
    void showReliability();

    /**
     * @brief Menu para mostrar o número máximo de comboios que podem viajar simultaneamente entre duas estações escolhidas pelo utilizador
     **/
    void showMaxNTrainsSimultaneously();
    /**
     * @brief Menu para mostrar os pares que requerem a maior quantidade de comboios para aproveitar a máxima capacidade da rede ferroviária existente
     **/
    void showPairsRequiredMostTrains();
    /**
     * @brief Menu para mostrar onde a administração deve atribuir maiores orçamentos para a compra e manutenção dos comboios
     **/
    void showLargerBudget();
    /**
     * @brief Menu para mostrar o número máximo de comboios que conseguem chegar simultaneamente a uma estação indicada pelo utilizador
     **/
    void showMaxNTrainsArriving();
    /**
     * @brief Método que obtém o ServiceMetric
     * @return Objeto da classe ServiceMetric correspondente
     **/
    ServiceMetrics* getService();
    /**
     * @brief Método que define o service do menu
     * @param service ServiceMetric que o menu vai adotar
     **/
    void setService(ServiceMetrics* service);
protected:
    ServiceMetrics* service;
};


#endif //DA_PROJ1_MENU_H
