#include <iostream>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include "Grafo.cpp"
#include "Menu.h"
using namespace std;

int main() {
    Grafo graph("../stations.csv", "../network.csv");
    Menu* m = new Menu();

    m->showMenu();
}
