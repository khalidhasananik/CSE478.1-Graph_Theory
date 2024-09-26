#include <bits/stdc++.h>
#define maxNodes 100

using namespace std;

int graph[maxNodes][maxNodes]; 
int deg[maxNodes];
int core[maxNodes];

void kCoreDecomposition(int n)
{
    bool processed[maxNodes] = {false};
    int tempDegree[maxNodes];

    for (int i = 0; i < n; ++i)
    {
        tempDegree[i] = deg[i];
    }

    int initialCore = 0;
    
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

        if (minDegreeNode != -1)
        {
            processed[minDegreeNode] = true;
            initialCore = max(initialCore, minDegree);
             core[minDegreeNode] = initialCore;

            for (int i = 0; i < n; ++i)
            {
                if (graph[minDegreeNode][i] == 1 && !processed[i])
                {
                    tempDegree[i]--;// Update the degrees of its neighbors
                }
            }
        }
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

    kCoreDecomposition(n);

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
