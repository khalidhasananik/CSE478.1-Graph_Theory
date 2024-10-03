#include <bits/stdc++.h>
#define maxNodes 100

using namespace std;

int graph[maxNodes][maxNodes]; 
int deg[maxNodes];
int core[maxNodes];
int sat[maxNodes];       
int colors[maxNodes];           
bool availableColors[maxNodes]; 

// void kCoreDecomposition(int n)
// {
//     bool processed[maxNodes] = {false};
//     int tempDegree[maxNodes];

//     for (int i = 0; i < n; ++i)
//     {
//         tempDegree[i] = deg[i];
//     }

//     int initialCore = 0;
    
//      for (int step = 0; step < n; ++step)
//     {
//         int minDegreeNode = -1;
//         int minDegree = maxNodes;

//         // Find the unprocessed node with the minimum degree
//         for (int i = 0; i < n; ++i)
//         {
//             if (!processed[i] && tempDegree[i] < minDegree)
//             {
//                 minDegree = tempDegree[i];
//                 minDegreeNode = i;
//             }
//         }

//         if (minDegreeNode != -1)
//         {
//             processed[minDegreeNode] = true;
//             initialCore = max(initialCore, minDegree);
//              core[minDegreeNode] = initialCore;

//             for (int i = 0; i < n; ++i)
//             {
//                 if (graph[minDegreeNode][i] == 1 && !processed[i])
//                 {
//                     tempDegree[i]--;// Update the degrees of its neighbors
//                 }
//             }
//         }
//     }
// }



int findMaxSatVertex(int n)
{
    int maxSat = -1;
    int maxDeg = -1;
    int selectedVertex = -1;

    for (int i = 0; i < n; ++i)
    {
        if (colors[i] == -1)
        { // Only consider uncolored vertices
            if (sat[i] > maxSat || (sat[i] == maxSat && deg[i] > maxDeg))
            {
                maxSat = sat[i];
                maxDeg = deg[i];
                selectedVertex = i;
            }
        }
    }
    return selectedVertex;
}

void updateSat(int n, int vertex)
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


void dsatur(int n)
{
    for (int i = 0; i < n; ++i)
    {
        colors[i] = -1; //all vertices uncolored
        sat[i] = 0; //all saturation 0
    }

    //kCoreDecomposition(n);

    // int sortedVertices[maxNodes];
    // for (int i = 0; i < n; ++i)
    // {
    //     sortedVertices[i] = i;
    // }
    // sort(sortedVertices, sortedVertices + n, [](int a, int b)
    //      { return core[a] > core[b]; });

    // cout << "Sorted Vertices:\n";

    // for(int i=0; i<n; i++)
    // {
    //     cout << sortedVertices[i] << " ";
    // }

    for (int i = 0; i < n; ++i)
    {
        int vertex = findMaxSatVertex(n);

        for (int j = 0; j < n; ++j)
        {
            availableColors[j] = true; //find smallest color
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

        colors[vertex] = color;
        updateSat(n, vertex);
    }
}



int main()
{
    int n, edges;
    cout << "Enter the number of vertices: ";
    cin >> n;

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
    cout << "Enter the edges in (u v) form: " << endl;

    for (int i = 0; i < edges; ++i)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }

    // kCoreDecomposition(n);

    // int sortedVertices[maxNodes];
    // for (int i = 0; i < n; ++i)
    // {
    //     sortedVertices[i] = i;
    // }
    // sort(sortedVertices, sortedVertices + n, [](int a, int b)
    //      { return core[a] > core[b]; });

    // cout << "Sorted Vertices:\n";

    // for(int i=0; i<n; i++)
    // {
    //     cout << sortedVertices[i] << " ";
    // }

    dsatur(n);

    cout << "Vertex Colors:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Vertex " << i << "'s color is " << colors[i] << endl;
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

