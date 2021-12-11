#include <vector>
#include "graph.h"

typedef struct Node{
    int numero;
    int predecessore;
    int dist;
    char colore; // W - White, G - Grey, B - Black
    std::vector<int> Adj;

    bool operator == (const Node n) const {
        return (numero == n.numero && predecessore == n.predecessore && dist == n.dist && colore == n.colore);
    };

    bool operator != (const Node n) const {
        return !(numero == n.numero && predecessore == n.predecessore && dist == n.dist && colore == n.colore);
    };
} Node;

typedef std::vector<Node> Graph;

void print_graph (Graph G) {
    for (int i=0; i<(int)G.size(); i++) {
        std::cout << "[" <<i<< "] -> (predecessore) " << "[" << G[i].predecessore << "]. Dist: " << G[i].dist << std::endl;
    }
}

