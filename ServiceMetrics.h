/*********************************************************************
 * @file  ServiceMetrics.h
 *
 * @brief Declaração da classe ServiceMetrics
 *********************************************************************/

#ifndef DA_PROJ1_SERVICEMETRICS_H
#define DA_PROJ1_SERVICEMETRICS_H
#include <string>
#include "Grafo.h"

/**
 * @class ServiceMetrics
 * @brief Classe com os métodos necessários para a resolução do problema inicial
 **/
class ServiceMetrics{
public:
    ServiceMetrics();
    ServiceMetrics(Grafo* grafo);
    /**
     * @brief Método que calcula o número máximo de comboios que podem viajar simultaneamente entre duas estações específicas
     * @param origin Nome da estação de origem
     * @param destiny Nome da estação de destino
     * @return Número máximo de comboios que podem viajar simultaneamente entre duas estações específicas
     **/
    int maxNTrainsSimultaneously(std::string origin, std::string destiny);

    /**
     * @brief Método que determina, entre todos os pares de estações, aqueles que requerem a maior quantidade de comboios para aproveitar a máxima capacidade da rede ferroviária existente
     * @return Pares de estações
     **/
    std::vector<std::string> pairsRequireMostTrains();

    /**
     * @brief Método que indica onde a administração deve atribuir maiores orçamentos para a compra e manutenção dos comboios
     * @return Municípios e Distritos com maior necessidade de investimento
     **/
    std::string largerBudget();

    /**
     * @brief Método que reporta o número máximo de comboios que conseguem chegar simultaneamente a uma estação indicada
     * @param station Nome da estação pretendida
     * @return Número de comboios que conseguem chegar simultaneamente à estação
     * **/
    int maxNTrainsArriving(std::string station);
protected:
    Grafo* graph;
};

#endif //DA_PROJ1_SERVICEMETRICS_H
