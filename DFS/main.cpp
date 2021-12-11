#include <iostream>
#include "graph.h"
using namespace std;

void DFS (Graph &G);
void DFS_visit (Graph &G, int node, int& time);

int main()
{
    Graph G;

    Node U;
    U.numero = 0;
    U.Adj.assign({1, 2});

    Node X;
    X.numero = 1;
    X.Adj.assign({2});

    Node V;
    V.numero = 2;
    V.Adj.assign({3});

    Node Y;
    Y.numero = 3;
    Y.Adj.assign({1});

    Node W;
    W.numero = 4;
    W.Adj.assign({3, 5});

    Node Z;
    Z.numero = 5;
    Z.Adj.assign({5});

    G.push_back(U);
    G.push_back(X);
    G.push_back(V);
    G.push_back(Y);
    G.push_back(W);
    G.push_back(Z);

    DFS(G);

    print_DFS(G);
    return 0;
}

void DFS (Graph &G) {
    for (auto& i: G) {
        i.colore = 'W';
        i.predecessore = -1;
    }

    int tempo = 0;

    for (auto& i: G) {
        if (i.colore == 'W') {
            DFS_visit(G, i.numero, tempo);
        }
    }
}
void DFS_visit (Graph &G, int node, int& time) {
    G[node].colore = 'G';
    time++;
    G[node].tempo_scoperta = time;

    for (auto i: G[node].Adj) {
        if (G[i].colore == 'W') {
            G[i].predecessore = G[node].numero;
            DFS_visit (G, i, time);
        }
    }
    G[node].colore = 'B';
    time++;
    G[node].tempo_fine = time;
}
