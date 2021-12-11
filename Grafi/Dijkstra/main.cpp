#include <iostream>
#include "graph.h"
#include <queue>
#include <climits>
using namespace std;

#define QueueNode priority_queue<Node, vector<Node>, greater<vector<Node>::value_type> >

void Dijkstra (Graph& G);
void init_queue (QueueNode& Q, Graph G);
int extract_min (QueueNode& Q);
void Relax (Graph& G, int first_node, int second_node, int w);

int main()
{
    Graph G;

    Node A;
    A.numero = 0;
    A.Adj.emplace_back(1, 10);
    A.Adj.emplace_back(2, 3);

    Node B;
    B.numero = 1;
    B.Adj.emplace_back(2, 1);
    B.Adj.emplace_back(3, 2);

    Node C;
    C.numero = 2;
    C.Adj.emplace_back(1, 4);
    C.Adj.emplace_back(3, 8);
    C.Adj.emplace_back(4, 2);

    Node D;
    D.numero = 3;
    C.Adj.emplace_back(4, 7);

    Node E;
    E.numero = 4;
    E.Adj.emplace_back(3, 5);

    G.push_back(A);
    G.push_back(B);
    G.push_back(C);
    G.push_back(D);
    G.push_back(E);

    // print_adj(G);

    Dijkstra(G);

    print_graph(G);

    return 0;
}

void Dijkstra (Graph& G) {
    for (auto& i: G) {
        i.predecessore = -1;
        i.dist = INT_MAX;
    }
    G[0].predecessore = -1;
    G[0].dist = 0;
    vector<int> S;

    QueueNode Q;
    init_queue(Q, G); // Theta (V * logV), where V is number of nodes of the graph G

    /* DEBUG
    while ( !Q.empty())
      {
          cout << Q.top().numero<< " " << Q.top().dist << endl;
          Q.pop();
      }
    init_queue(Q, G);
    */

    while (!Q.empty()) {
        int node = extract_min(Q);
        S.push_back(node);
        /* DEBUG
        cout << "S: ";
        for (auto i: S) cout << i << " ";
        cout << endl;
        */
        for (auto i: G[node].Adj) {
            Relax(G, node, i.first, i.second);
        }
    }
}

void init_queue (QueueNode& Q, Graph G) {
    for (auto i: G) {
        Q.emplace(i);
    }
}

int extract_min (QueueNode& Q) {
    Node n = Q.top();
    Q.pop();
    return n.numero;
}

/*
 * Assume the first node is the one entered in S list
 * w is the weight of the edge from first node to second node
*/
void Relax (Graph& G, int first_node, int second_node, int w) {
    if (G[second_node].dist > G[first_node].dist + w) {
        //cout << "Relax\n";
        G[second_node].dist = G[first_node].dist + w;
        G[second_node].predecessore = first_node;
    }
}
