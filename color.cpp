#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    int n;
    vector<vector<int>> adj;
    vector<int> col;
    vector<int> sat;

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
    vector<int> deg(n);  // Degree of each vertex
    vector<int> pos(n);  // Position array
    vector<int> vert(n); // Vertex array

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

    //     Ver: 2  5  0  1  4  6  7  10  3  9  11  12  13  8  14
    //     Pos: 2  3  0  8  4  1  5  6  13  9  7  10  11  12  14
    //     Deg: 3  3  4  2  3  4  3  3  1  2  3  2  2  2  1

    vector<int> temp(n);
    temp[0] = vert[0];
    temp[1] = 0;
    temp[2] = 6;
    temp[3] = 8;
    temp[4] = 7;
    temp[5] = 1;
    temp[6] = 3;
    temp[7] = 7;
    temp[8] = 13;

    for (int i = 0; i < n; i++)
    {
        int v = temp[i];
        g.col[v] = minColor;
        for (int j = 0; j < g.adj(v); j++)
        {
            int u = g.adj[v][j];
        }
    }
}

// for (int i = 0; i < n;i++)
// {
//     int v = temp[i];
//     for (int j = 0; j < g.adj[v].size(); j++)
//     {
//         int u = g.adj[v][j];
//         if (g.col[u] != -1)
//             continue;
//         g.sat[u]++;
//         if (g.sat[u] == 1)
//             g.col[u] = 0;
//         else
//         {
//             int maxSat = 0;
//             for (int k = 0; k < g.adj[u].size(); k++)
//             {
//                 int w = g.adj[u][k];
//                 if (g.col[w] != -1)
//                     continue;
//                 if (g.sat[w] > maxSat)
//                     maxSat = g.sat[w];
//             }
//             g.col[u] = maxSat;
//         }
//         temp.push_back(u);
//     }
// }

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
