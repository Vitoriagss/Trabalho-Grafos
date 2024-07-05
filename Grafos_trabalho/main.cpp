#include "Graph.h"
#include <tuple>
#include <vector>
#include <iostream>
#include <iomanip>
#include "stdio.h"
#include "stdlib.h"

using namespace std;

void printMenu() {
    std::cout << "===== Menu =====\n";
    std::cout << "1. Imprimir Matriz de Adjacência\n";
    std::cout << "2. Imprimir Lista de Adjacência\n";
    std::cout << "3. Coloração de Grafos (Algoritmo de Brelaz)\n";
    std::cout << "4. Imprimir arvore geradora minima\n";
    std::cout << "5. Calcular Fluxo Máximo (Ford-Fulkerson)\n";
    std::cout << "6. Calcular Emparelhamento Máximo (Grafo Bipartido)\n";
    std::cout << "7. Sair\n";
    std::cout << "Escolha uma opção: ";
}

int main() {
    vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<tuple<int, int, int>> arestas = {
        {1, 2, 5}, {1, 3, 8}, {1, 4, 3},
        {2, 3, 6}, {2, 5, 9}, {3, 4, 2},
        {3, 6, 7}, {4, 7, 4}, {5, 6, 1},
        {5, 8, 5}, {6, 9, 3}, {7, 8, 2},
        {7, 10, 6}, {8, 9, 4}, {9, 10, 7}
    };

    Graph teste(vertices, arestas);
    int op = 0;

    do {
        printMenu();
        std::cin >> op;

        switch (op) {
            case 1:
                std::cout << "\nMatriz de Adjacencia:\n";
                teste.printMatrix();
                std::cout << "\n";
                break;
            case 2:
                std::cout << "\nLista de Adjacencia:\n";
                teste.printList();
                std::cout << "\n";
                break;
            case 3:
                std::cout << "\nColoracao de Grafos (Algoritmo de Brelaz):\n";
                teste.brelazColoring();
                teste.printColors();
                std::cout << "\n";
                break;
            case 4:
                std::cout << "\nArvore geradora minima:\n";
                teste.prim();
                std::cout << "\n";
                break;
            case 7:
                std::cout << "\n Programa encerrado\n";
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente.\n\n";
                break;
        }
    } while (op != 7);

    getchar();
    return 0;
}