#include <bits/stdc++.h>

using namespace std;

// Graph data structure using adjacency list
class Graph
{
public:
    int n;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list for the graph

    // Constructor
    Graph(int n) : n(n)
    {
        adj.resize(n);
    }

    // Add an undirected edge between u and v
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

// K-Core decomposition function
void kCoreDecomposition(Graph &g, vector<int> &core)
{
    int n = g.n;
    vector<int> deg(n);        // Degree of each vertex
    vector<int> bin(n + 1, 0); // Bin array
    vector<int> pos(n);        // Position array
    vector<int> vert(n);       // Vertex array

    // Initialize degree of each vertex
    for (int i = 0; i < n; i++)
    {
        deg[i] = g.adj[i].size();
    }

    // deg = [3, 3, 4, 2, 3, 4, 3, 3, 1, 2, 3, 2, 2, 2, 1]

    // Find the maximum degree
    int md = *max_element(deg.begin(), deg.end());

    // md = 4

    // Initialize bin array to count vertices of each degree
    for (int i = 0; i < n; i++)
    {
        bin[deg[i]]++;
    }

    // bin = [0, 2, 5, 6, 2]

    // Starting positions in the bin array
    int start = 0;
    for (int d = 0; d <= md; d++)
    {
        int num = bin[d];
        bin[d] = start;
        start += num;
    }
    // bin = [0, 0, 2, 7, 13]

    // Initialize pos and vert arrays
    for (int v = 0; v < n; v++)
    {
        pos[v] = bin[deg[v]]; // v=1, deg[1]=3, bin[3]=8, pos[1]=8
        vert[pos[v]] = v;     // vert[8]=1
        bin[deg[v]]++;        // deg[1] = 3. bin[3] = 9
    }

    // pos = [7, 8, 13, 2, 9, 14, 10, 11, 0, 3, 4, 5, 6, 12, 1]
    // vert = [8, 14, 3, 9, 10, 11, 12, 0, 1, 4, 6, 7, 13, 2, 5]
    // bin = [0, 2, 7, 13, 15]

    // Adjust bin array for proper positions
    for (int d = md; d >= 1; d--)
    {
        bin[d] = bin[d - 1];
    }
    bin[0] = 0;

    // bin = [0, 0, 2, 7, 13]

    // Core decomposition
    for (int i = 0; i < n; i++)
    {
        int v = vert[i];
        core[v] = deg[v];

        for (int j = 0; j < g.adj[v].size(); j++)
        {
            int u = g.adj[v][j];
            if (deg[u] > deg[v])
            {
                int du = deg[u];
                int pu = pos[u];
                int pw = bin[du];
                int w = vert[pw];

                if (u != w)
                {
                    pos[u] = pw;
                    vert[pw] = u;
                    pos[w] = pu;
                    vert[pu] = w;
                }

                bin[du]++;
                deg[u]--;
            }
        }
    }
}

int main()
{
    int n = 15; // Number of vertices in the graph
    Graph g(n);

    // Adding the edges to the graph (undirected)
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(3, 9);
    g.addEdge(2, 8);
    g.addEdge(2, 7);
    g.addEdge(2, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 14);
    g.addEdge(6, 13);
    g.addEdge(12, 13);
    g.addEdge(12, 5);
    g.addEdge(5, 11);
    g.addEdge(10, 11);
    g.addEdge(5, 4);
    g.addEdge(4, 10);
    g.addEdge(9, 10);

    // Vector to store the core number of each vertex
    vector<int> core(n, 0);

    // Perform K-Core decomposition
    kCoreDecomposition(g, core);

    vector<int> sortedVertices(n);

    // Output the core numbers

    map<int, int> coreMap;

    for (int i = 0; i < n; i++)
    {
        coreMap[i] = core[i];
    }

    // sort the map in terms of values

    sort(coreMap.begin(), coreMap.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.second < b.second; });

    for (auto &it : coreMap)
    {
        cout << "Vertex " << it.first << " has core number " << it.second << endl;
    }

    // cout << "Core numbers of the vertices:" << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     cout << "Vertex " << i << ": " << core[i] << endl;
    // }

    return 0;
}
