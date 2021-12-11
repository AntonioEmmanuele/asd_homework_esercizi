#include <iostream>
#include <climits>
#include <queue>
#include "graph.h"
using namespace std;

void BFS (Graph& G, Node& S);

int main()
{
    Graph G;

    Node S;
    S.numero = 0;
    S.Adj.assign({1, 3});

    Node R;
    R.numero = 1;
    R.Adj.assign({0, 2});

    Node V;
    V.numero = 2;
    V.Adj.assign({1});

    Node W;
    W.numero = 3;
    W.Adj.assign({0, 4, 5});

    Node T;
    T.numero = 4;
    T.Adj.assign({3, 5, 6});

    Node X;
    X.numero = 5;
    X.Adj.assign({3, 4, 6, 7});

    Node U;
    U.numero = 6;
    U.Adj.assign({4, 5, 7});

    Node Y;
    Y.numero = 7;
    Y.Adj.assign({5, 6});

    G.push_back(S);
    G.push_back(R);
    G.push_back(V);
    G.push_back(W);
    G.push_back(T);
    G.push_back(X);
    G.push_back(U);
    G.push_back(Y);

    BFS(G, G[0]);

    print_graph(G);

    return 0;
}

void BFS (Graph& G, Node& S) {
    for (auto& i: G) {
        if (i != S) {
            i.colore = 'W';
            i.dist = INT_MAX;
            i.predecessore = -1;
        }
    }

    S.colore = 'G';
    S.dist = 0;
    S.predecessore = -1;

    queue<Node> Q;
    Q.push (S);

    //cout << "Sorgente ispezionata.\n";
    while (!Q.empty()) {
        Node temp = Q.front();
        //cout << "Prendo il nodo: " << temp.numero << endl;
        Q.pop();
        for (auto& i: temp.Adj) {
            if (G[i].colore == 'W') {
                G[i].colore = 'G';
                G[i].dist = temp.dist + 1;
                G[i].predecessore = temp.numero;

                Q.push(G[i]);
                //cout << "Pusho il nodo: " << G[i].numero << endl;
            }
        }
        G[temp.numero].colore = 'B';
        //cout << "Nodo " << G[temp.numero].numero << " posto a nero." << endl;
    }
}
