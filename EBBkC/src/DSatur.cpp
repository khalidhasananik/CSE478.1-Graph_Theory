#include <iostream>
#include <vector>
#include <algorithm>

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

// Graph Coloring using Saturation Degree (DSATUR) with Bin Sorting and Efficient Color Management
void graphColoring(Graph &g)
{
    int n = g.n;
    vector<int> deg(n);                                             // Degree of each vertex
    vector<int> satDegree(n, 0);                                    // Saturation degree of each vertex
    vector<int> color(n, -1);                                       // Color assigned to each vertex
    vector<int> smallestAvailable(n, 0);                            // Tracks the smallest available color for each vertex
    vector<vector<bool>> availableColors(n, vector<bool>(n, true)); // Available colors for each vertex

    // Bins for saturation degree
    vector<int> bin(n + 1, 0); // Bin array for saturation degrees (range 0 to n)
    vector<int> pos(n);        // Position array
    vector<int> vert(n);       // Vertex array

    // Initialize degree of each vertex and vertex list
    for (int i = 0; i < n; i++)
    {
        deg[i] = g.adj[i].size();
        vert[i] = i; // Initialize vert to contain all vertices
    }

    // Initialize bin for saturation degrees
    for (int i = 0; i < n; i++)
    {
        bin[satDegree[i]]++;
    }

    // Starting positions in the bin array
    int start = 0;
    for (int d = 0; d <= n; d++)
    {
        int num = bin[d];
        bin[d] = start;
        start += num;
    }

    // Initialize pos and vert arrays
    for (int v = 0; v < n; v++)
    {
        pos[v] = bin[satDegree[v]];
        vert[pos[v]] = v;
        bin[satDegree[v]]++;
    }

    // Adjust bin array for proper positions
    for (int d = n; d >= 1; d--)
    {
        bin[d] = bin[d - 1];
    }
    bin[0] = 0;

    // Graph Coloring using DSATUR with bin sorting
    for (int step = 0; step < n; step++)
    {
        // Find the vertex with the highest saturation degree that is not colored
        int v = -1;
        for (int i = n; i >= 0; i--)
        { // Start from the highest possible saturation degree
            if (bin[i] < n)
            { // Check if there are any vertices in this bin
                int idx = bin[i];
                while (idx < n && color[vert[idx]] != -1)
                {
                    idx++;
                }
                if (idx < n)
                {
                    v = vert[idx];
                    break;
                }
            }
        }

        if (v == -1)
            break; // No more uncolored vertices

        // Use the secondary bin (smallestAvailable) to find the smallest available color for vertex v
        int c = smallestAvailable[v];

        // Assign the color to vertex v
        color[v] = c;

        // Update the saturation degree of adjacent vertices
        for (int u : g.adj[v])
        {
            if (color[u] == -1)
            { // Only update uncolored vertices
                if (availableColors[u][c])
                {
                    availableColors[u][c] = false; // Mark this color as unavailable

                    // Find the next smallest available color for u
                    while (smallestAvailable[u] < n && !availableColors[u][smallestAvailable[u]])
                    {
                        smallestAvailable[u]++;
                    }

                    int oldSat = satDegree[u];
                    satDegree[u]++;

                    // Move vertex u to the new bin
                    int pu = pos[u];
                    int pw = bin[oldSat + 1];

                    if (pu != pw)
                    {
                        // Swap positions in the vert array
                        int w = vert[pw];
                        pos[u] = pw;
                        vert[pw] = u;
                        pos[w] = pu;
                        vert[pu] = w;
                    }

                    // Increment the start of the new bin
                    bin[oldSat + 1]++;
                }
            }
        }
    }

    // Output the color assigned to each vertex
    cout << "Vertex Colors:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Vertex " << i << ": Color " << color[i] << endl;
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

    // Perform Graph Coloring using DSATUR with bin sorting
    graphColoring(g);

    return 0;
}
