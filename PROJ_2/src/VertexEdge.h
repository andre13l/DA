/*********************************************************************
 * @file  VertexEdge.h
 *
 * @brief Declaração das classes Vertex e Edge
 *********************************************************************/

#ifndef DA_PROJ1_VERTEXEDGE_H
#define DA_PROJ1_VERTEXEDGE_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

/**
 * @class Edge
 * @brief Classe relativa a uma aresta do grafo
 **/
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/
/**
 * @class Vertex
 * @brief Classe relativa a um vértice do grafo
 **/
class Vertex {
public:
    Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    /**
     * @brief Método que obtém o id do vértice
     * @return Id do vértice
     **/
    int getId() const;
    /**
     * @brief Método que obtém o nome do vértice
     * @return Nome do vértice
     **/
    std::string getName() const;
    /**
     * @brief Método que obtém o distrito do vértice
     * @return Distrito do vértice
     **/
    std::string getDistrict() const;
    /**
     * @brief Método que obtém o município do vértice
     * @return Município do vértice
     **/
    std::string getMunicipality() const;
    /**
     * @brief Método que obtém a freguesia do vértice
     * @return Freguesia do vértice
     **/
    std::string getTownship() const;
    /**
     * @brief Método que obtém a linha do vértice
     * @return Linha do vértice
     **/
    std::string getLine() const;
    /**
     * @brief Método que obtém as arestas adjacentes
     * @return Vetor com as arestas adjacentes
     **/
    std::vector<Edge *> getAdj() const;
    /**
     * @brief Método para verificar se o vértice é visitado
     * @retval true Quando o vértice é visitado
     * @retval false Quando o vértice não é visitado
     **/
    bool isVisited() const;
    /**
     * @brief Método que obtém a aresta que tem como destino este vértice
     * @return Aresta que tem como destino este vértice
     **/
    Edge *getPath() const;
    /**
     * @brief Método que obtém as arestas de entrada
     * @return Vetor com as arestas de entrada
     **/
    std::vector<Edge *> getIncoming() const;
    /**
     * @brief Método que define o id do vértice
     * @param info Id do vértice
     **/
    void setId(int info);
    /**
     * @brief Método que define se o vértice é visitado ou não
     * @param visited true se é visitado ou false se não é visitado
     **/
    void setVisited(bool visited);
    /**
     * @brief Método que define a aresta que tem como destino este vértice
     * @param path Aresta que tem como destino este vértice
     **/
    void setPath(Edge *path);
    /**
     * @brief Método para adicionar uma aresta
     * @param dest Vértice de destino
     * @param w Capacidade da aresta
     * @param type Tipo da aresta
     * @return Aresta criada
     **/
    Edge * addEdge(Vertex *dest, double w, std::string type);
    /**
     * @brief Método para remover uma aresta
     * @param destID Id do vértice de destino
     * @retval true Quando a aresta é removida com sucesso
     * @retval false Quando a aresta não existe previamente
     **/
    bool removeEdge(int destID);
    /**
     * @brief Método para remover arestas adjacentes
     **/
    void removeOutgoingEdges();

protected:
    int id;                // identifier
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    /**
     * @brief Método que elimina uma aresta
     * @param edge Aresta a ser eliminada
     **/
    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, std::string type);

    /**
     * @brief Método que obtém o vértice de destino
     * @return Vértice de destino
     **/
    Vertex * getDest() const;
    /**
     * @brief Método que obtém a capacidade da aresta
     * @return Capacidade da aresta
     **/
    double getWeight() const;
    /**
     * @brief Método que obtém o tipo da aresta
     * @return Tipo da aresta
     **/
    std::string getType() const;
    /**
     * @brief Método para verificar que a aresta é selecionada ou não
     * @retval true Quando a aresta é selecionada
     * @retval false Quando a aresta não é selecionada
     **/
    bool isSelected() const;
    /**
     * @brief Método que obtém o vértice de origem
     * @return Vértice de origem
     **/
    Vertex * getOrig() const;
    /**
     * @brief Método que obtém a aresta inversa
     * @return Aresta inversa
     **/
    Edge *getReverse() const;
    /**
     * @brief Método que obtém o fluxo
     * @return Fluxo
     **/
    double getFlow() const;
    /**
     * @brief Método que obtém o custo
     * @return Custo
     **/
    int getCost() const;
    /**
     * @brief Método que define se a aresta é selecionada ou não
     * @param selected true para selecionar a aresta e false para não selecionar a aresta
     **/
    void setSelected(bool selected);
    /**
     * @brief Método que define a aresta inversa
     * @param reverse Aresta inversa
     **/
    void setReverse(Edge *reverse);
    /**
     * @brief Método que define o fluxo
     * @param flow Fluxo
     **/
    void setFlow(double flow);
    /**
     * @brief Método que define o custo
     * @param cost Custo
     **/
    void setCost(int cost);
protected:
    Vertex *dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    std::string type;
    int cost;

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};


#endif //DA_PROJ1_VERTEXEDGE_H
