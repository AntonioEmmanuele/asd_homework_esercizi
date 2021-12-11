#ifndef _GRAPH_
#define _GRAPH_

#include <vector>

typedef struct Node{
    int numero;
    int predecessore;
    int dist;
    char colore; // W - White, G - Grey, B - Black
    int tempo_scoperta;
    int tempo_fine;
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

void print_DFS (Graph G) {
    for (int i=0; i<(int)G.size(); i++) {
        std::cout << "[" <<i<< "] -> (predecessore) " << "[" << G[i].predecessore << "]. Tempo scoperta: " << G[i].tempo_scoperta
        << ", tempo fine: " << G[i].tempo_fine << std::endl;
    }
}

#endif // _GRAPH_

