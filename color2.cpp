#include <bits/stdc++.h>
#include "dll.cpp"

using namespace std;

class Graph
{
public:
    int n;
    vector<vector<int>> adj;
    vector<int> sat;
    vector<int> col;

    Graph(int n) : n(n)
    {
        adj.resize(n);
        col.resize(n);
        sat.resize(n);

        for (int i = 0; i < n; i++)
        {
            col[i] = -1;
            sat[i] = 0;
        }
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

void dSatur(Graph &g)
{
    int n = g.n;
    vector<int> deg(n);    // Degree of each vertex
    vector<int> pos(n);    // Position array
    vector<int> vert(n);   // Vertex array
    vector<int> colors(n); // All available colors
    DoublyLinkedList dll;
    vector<DoublyLinkedList::Node *> nodePointer(n);
    vector<DoublyLinkedList::Node *> nodeLocator(n);

    for (int i = 0; i < n; i++)
        deg[i] = g.adj[i].size();

    // deg = [3, 3, 4, 2, 3, 4, 3, 3, 1, 2, 3, 2, 2, 2, 1]

    int md = *max_element(deg.begin(), deg.end());

    vector<int> bin(md + 1, 0);

    for (int i = 0; i < n; i++)
        bin[deg[i]]++;

    reverse(bin.begin(), bin.end());

    int start = 0;
    for (int d = 0; d <= md; d++)
    {
        int num = bin[d];
        bin[d] = start;
        start += num;
    }

    reverse(bin.begin(), bin.end());

    for (int v = 0; v < n; v++)
    {
        pos[v] = bin[deg[v]];
        vert[pos[v]] = v;
        bin[deg[v]]++;
    }

    for (int d = 0; d < md; d++)
        bin[d] = bin[d + 1];
    bin[md] = 0;

    // Ver: 2  5  0  1  4  6  7  10  3  9  11  12  13  8  14
    // Pos: 2  3  0  8  4  1  5  6  13  9  7  10  11  12  14
    // Deg: 3  3  4  2  3  4  3  3  1  2  3  2  2  2  1

    // Algorithm:
    // {-select a node
    //  -check available colors
    //  -color it with the minimum color
    //  -update saturation of neighbors
    //  -select next node with max saturation}
    // repeat

    g.col[vert[0]] = 0; // Colors vertex with highest degree

    for (int i = n - 1; i >= 0; i--)
    {
        dll.insertFront(vert[i]);
        nodeLocator[i] = dll.getHead();
    }

    // Push the adjacents of the colored vertex to the list
    // for (int i = 0; i < g.adj[vert[0]].size(); i++)
    // {
    //     int neighbor = g.adj[vert[0]][i];
    //     g.sat[neighbor] += 1;                         // Saturation set to 1
    //     dll.insertFront(neighbor);                    // Pushed to list
    //     nodePointer[g.sat[neighbor]] = dll.getHead(); // The positon of sat=1 is saved
    // }

    // Traversing all nodes [O(n-1)]
    while (dll.getHead() != nullptr)
    {
        int v = dll.getHead()->data;
        dll.deleteFront();

        for (int i = 0; i < g.adj[v].size(); i++)
        {
            int neighbor = g.adj[v][i];

            // Updating saturation
            if (g.col[neighbor] == -1)
            {
                g.sat[neighbor] += 1;
                if (g.sat[neighbor] <= nodePointer.size())
                    dll.insertBefore(nodePointer[g.sat[neighbor]], neighbor);
                else
                {
                    dll.insertFront(neighbor);
                    nodePointer[g.sat[neighbor]] = dll.getHead();
                }
            }
        }
    }
}

int main()
{
    int n = 15;
    Graph g(n);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 6);
    g.addEdge(2, 7);
    g.addEdge(2, 8);
    g.addEdge(3, 9);
    g.addEdge(4, 5);
    g.addEdge(4, 10);
    g.addEdge(5, 11);
    g.addEdge(5, 12);
    g.addEdge(6, 7);
    g.addEdge(6, 13);
    g.addEdge(7, 14);
    g.addEdge(9, 10);
    g.addEdge(10, 11);
    g.addEdge(12, 13);

    dSatur(g);

    // for (int i = 0; i < n; i++)
    //     cout << "Vertex " << i << ": " << g.col[i] << endl;

    return 0;
}
