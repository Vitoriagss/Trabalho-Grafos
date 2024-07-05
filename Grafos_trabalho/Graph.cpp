#include "Graph.h"
#include <tuple>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <limits.h>
#include <numeric>

using namespace std;

Graph::Graph(std::vector<int> v, std::vector<std::tuple<int, int, int>> e, bool bi) : bidirectional(bi), colors(v.size(), -1) {
    // Copia os vértices e os organiza
    vertices = v;
    std::sort(vertices.begin(), vertices.end());

    // Copia as arestas
    edges = e;
    std::sort(edges.begin(), edges.end());
}

void Graph::printMatrix() {
    int n = vertices.size();
    // Cria a matriz
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    // Inicializa com 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    // Dá valores à matriz
    for (int k = 0; k < edges.size(); k++) {
        int u = std::get<0>(edges[k]) - 1;
        int v = std::get<1>(edges[k]) - 1;
        int weight = std::get<2>(edges[k]);

        matrix[u][v] = weight;

        if (bidirectional) {
            matrix[v][u] = weight;
        }
    }

    // Imprime a matriz
    std::cout << "Matriz de adjacências:\n  ";
    for (int i = 0; i < n; i++) {
        std::cout << vertices[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < n; i++) {
        std::cout << vertices[i] << " ";
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Deleta a matriz
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Graph::printList() {
    // Inicia o vetor
    std::vector<std::list<std::pair<int, int>>> adj(vertices.size());

    // Preenche a lista
    for (int i = 0; i < edges.size(); i++) {
        int u = std::get<0>(edges[i]) - 1;
        int v = std::get<1>(edges[i]) - 1;
        int weight = std::get<2>(edges[i]);

        adj[u].push_back({v + 1, weight});
        if (bidirectional) {
            adj[v].push_back({u + 1, weight});
        }
    }

    // Imprime a lista
    std::cout << "Lista de adjacências:\n";
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i] << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
            std::cout << "(" << it->first << ", " << it->second << ") ";
        }
        std::cout << "\n";
    }
}

void Graph::prim() {
    vector<bool> visited(vertices.size(), false);
    vector<int> parent(vertices.size(), -1);
    vector<int> key(vertices.size(), numeric_limits<int>::max());

    key[0] = 0;

    for (int i = 0; i < vertices.size(); i++) {
        int minKey = numeric_limits<int>::max();
        int u = -1;

        for (int j = 0; j < vertices.size(); j++) {
            if (!visited[j] && key[j] < minKey) {
                minKey = key[j];
                u = j;
            }
        }

        visited[u] = true;

        for (int v = 0; v < vertices.size(); v++) {
            if (!visited[v] && getEdgeWeight(vertices[u], vertices[v]) != 0 && getEdgeWeight(vertices[u], vertices[v]) < key[v]) {
                key[v] = getEdgeWeight(vertices[u], vertices[v]);
                parent[v] = u;
            }
        }
    }

    cout << "Árvore geradora mínima:" << endl;
    for (int i = 1; i < vertices.size(); i++) {
        cout << vertices[parent[i]] << " -> " << vertices[i] << " : " << getEdgeWeight(vertices[parent[i]], vertices[i]) << endl;
    }
}

int Graph::getEdgeWeight(int u, int v) {
    for (int i = 0; i < edges.size(); i++) {
        if (std::get<0>(edges[i]) == u && std::get<1>(edges[i]) == v) {
            return std::get<2>(edges[i]);
        }
        if (std::get<0>(edges[i]) == v && std::get<1>(edges[i]) == u) {
            return std::get<2>(edges[i]);
        }
    }
    return 0;
}

