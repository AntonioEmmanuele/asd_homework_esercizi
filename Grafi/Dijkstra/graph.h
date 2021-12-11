#ifndef _GRAPH_
#define _GRAPH_

#include <vector>

typedef struct Node{
    int numero;
    int predecessore;
    int dist;
    std::vector<std::pair<int, int>> Adj;

    bool operator == (const Node n) const {
        return (numero == n.numero && predecessore == n.predecessore && dist == n.dist);
    };

    bool operator != (const Node n) const {
        return !(numero == n.numero && predecessore == n.predecessore && dist == n.dist);
    };

    /*
     * priority queue uses these operators to sort the min-heap queue
    */
    bool operator > (const Node n) const {
        return (dist > n.dist);
    }

    bool operator < (const Node n) const {
        return (dist < n.dist);
    }
} Node;

typedef std::vector<Node> Graph;

void print_graph (Graph G) {
    for (int i=0; i<(int)G.size(); i++) {
        std::cout << "[" <<i<< "] -> (predecessore) " << "[" << G[i].predecessore << "]. Dist: " << G[i].dist << std::endl;
    }
}

void print_adj (Graph G) {
    for (int i=0; i<(int)G.size(); i++) {
        for (auto j = 0; j < (int)G[i].Adj.size(); j++) {
            std::cout << "(" << G[i].Adj.at(j).first << "," << G[i].Adj.at(j).second << ")" << "; ";
        }
        std::cout << std::endl;
    }
}

#endif // _GRAPH_

