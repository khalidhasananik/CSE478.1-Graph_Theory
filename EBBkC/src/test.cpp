#include <iostream>
#include <algorithm>
#include <queue>

#define maxNodes 100 // Maximum number of nodes in the graph

using namespace std;

int graph[maxNodes][maxNodes]; // Adjacency matrix representation
int deg[maxNodes];           // Degree of each vertex
int sat[maxNodes];       // Saturation degree for DSatur
int colors[maxNodes];           // Colors assigned to vertices
int core[maxNodes];             // Core numbers from k-core decomposition
bool availableColors[maxNodes]; // Array to keep track of available colors for a vertex

// Function to perform k-core decomposition
void kCoreDecomposition(int n)
{
    int tempDegree[maxNodes]; // Temporary array for degree counting
    bool processed[maxNodes] = {false};

    // Copy original degree information
    for (int i = 0; i < n; ++i)
    {
        tempDegree[i] = deg[i];
    }

    int current_core = 0;

    // Process nodes by their degrees using a simple greedy method
    for (int step = 0; step < n; ++step)
    {
        int minDegreeNode = -1;
        int minDegree = maxNodes;

        // Find the unprocessed node with the minimum degree
        for (int i = 0; i < n; ++i)
        {
            if (!processed[i] && tempDegree[i] < minDegree)
            {
                minDegree = tempDegree[i];
                minDegreeNode = i;
            }
        }

        // Mark this node as processed and assign it a core number
        if (minDegreeNode != -1)
        {
            processed[minDegreeNode] = true;
            current_core = max(current_core, minDegree);
            core[minDegreeNode] = current_core;

            // Update the degrees of its neighbors
            for (int i = 0; i < n; ++i)
            {
                if (graph[minDegreeNode][i] == 1 && !processed[i])
                {
                    tempDegree[i]--;
                }
            }
        }
    }
}

// Function to find the vertex with the maximum saturation
int findMaxSaturationVertex(int n)
{
    int maxSaturation = -1;
    int maxDegree = -1;
    int selectedVertex = -1;

    for (int i = 0; i < n; ++i)
    {
        if (colors[i] == -1)
        { // Only consider uncolored vertices
            if (sat[i] > maxSaturation || (sat[i] == maxSaturation && deg[i] > maxDegree))
            {
                maxSaturation = sat[i];
                maxDegree = deg[i];
                selectedVertex = i;
            }
        }
    }
    return selectedVertex;
}

// Function to update saturation degrees after coloring a vertex
void updateSaturation(int n, int vertex)
{
    for (int i = 0; i < n; ++i)
    {
        if (graph[vertex][i] == 1 && colors[i] == -1)
        { // If it's a neighbor and uncolored
            bool neighborColors[maxNodes] = {false};

            // Check all neighbors of this neighbor
            for (int j = 0; j < n; ++j)
            {
                if (graph[i][j] == 1 && colors[j] != -1)
                {
                    neighborColors[colors[j]] = true;
                }
            }

            // Count distinct colors used in the neighbors
            int distinctColors = 0;
            for (int k = 0; k < maxNodes; ++k)
            {
                if (neighborColors[k])
                {
                     distinctColors++;
                }
            }
            sat[i] = distinctColors;
        }
    }
}

// DSatur coloring algorithm
void dsatur(int n)
{
    // Initialize all vertices as uncolored
    for (int i = 0; i < n; ++i)
    {
        colors[i] = -1;
        sat[i] = 0;
    }

    // Perform k-core decomposition
    kCoreDecomposition(n);

    // Sort vertices based on core number in descending order
    int sortedVertices[maxNodes];
    for (int i = 0; i < n; ++i)
    {
        sortedVertices[i] = i;
    }
    sort(sortedVertices, sortedVertices + n, [](int a, int b)
         { return core[a] > core[b]; });

    cout << "Sorted Vertices:\n";

    for(int i=0; i<n; i++)
    {
        cout << sortedVertices[i] << " ";
    }

    // Start DSatur algorithm
    for (int i = 0; i < n; ++i)
    {
        int vertex = findMaxSaturationVertex(n);

        // Find the smallest available color for this vertex
        for (int j = 0; j < n; ++j)
        {
            availableColors[j] = true;
        }

        for (int j = 0; j < n; ++j)
        {
            if (graph[vertex][j] == 1 && colors[j] != -1)
            {
                availableColors[colors[j]] = false;
            }
        }

        int color;
        for (color = 0; color < n; ++color)
        {
            if (availableColors[color])
            {
                break;
            }
        }

        // Assign the color to the vertex
        colors[vertex] = color;

        // Update saturation degrees of neighbors
        updateSaturation(n, vertex);
    }
}

int main()
{
    int n, edges;
    cout << "Enter the number of vertices: ";
    cin >> n;

    // Initialize the adjacency matrix and degrees
    for (int i = 0; i < n; ++i)
    {
        deg[i] = 0;
        for (int j = 0; j < n; ++j)
        {
            graph[i][j] = 0;
        }
    }

    cout << "Enter the number of edges: ";
    cin >> edges;
    cout << "Enter the edges (u v) where u and v are vertex indices (0 to " << n - 1 << "):" << endl;
    for (int i = 0; i < edges; ++i)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }

    // Perform DSatur coloring
    dsatur(n);

    // Output the coloring result
    cout << "Vertex Colors:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Vertex " << i << " -> Color " << colors[i] << endl;
    }

    return 0;
}


// 0 1
// 0 3
// 0 2
// 1 4
// 1 5
// 3 9
// 2 8
// 2 7
// 2 6
// 6 7
// 7 14
// 6 13
// 12 13
// 12 5
// 5 11
// 10 11
// 5 4
// 4 10
// 9 10
