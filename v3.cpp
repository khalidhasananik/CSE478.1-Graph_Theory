#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int ***graph;
int n;
int finish = 0;

int max_sat()
{
    int maxSat = 0;
    int maxVer = -1;

    for (int i = 0; i < n; i++)
    {
        if ((graph[i][0][0] > maxSat) && (graph[i][1][0]) == -1)
        {
            maxSat = graph[i][0][0];
            maxVer = i;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if ((graph[i][0][0] == maxSat) && (graph[i][1][0] == -1))
        {
            if (graph[i][2][0] > graph[maxVer][2][0])
                maxVer = i;
        }
    }

    return maxVer;
}

void color(int v)
{
    int minColor = -1;
    for (int x = 0; x < n; x++)
        if (graph[v][4][x] == -1)
        {
            minColor = x;
            break;
        }

    graph[v][1][0] = minColor;

    for (int i = 0; i < graph[v][2][0]; i++)
    {
        int neighbor = graph[v][3][i];
        if (graph[neighbor][1][0] == -1)
        {
            graph[neighbor][0][0] += 1;
            graph[neighbor][4][minColor] = minColor;
        }
    }

    finish++;
    if (finish == n)
        return;

    color(max_sat());
    return;
}

int main()
{
    auto start = high_resolution_clock::now();
#ifndef BZMYSR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // BZMYSR

    cin >> n;
    graph = new int **[n];
    int maxDeg = 0;
    int maxVer = 0;

    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;

        graph[i] = new int *[5];
        graph[i][0] = new int[1]; // saturation
        graph[i][1] = new int[1]; // colored/uncolored
        graph[i][2] = new int[1]; // degree

        graph[i][0][0] = 0;
        graph[i][1][0] = -1;
        graph[i][2][0] = d;

        graph[i][3] = new int[d]; // neighbors
        graph[i][4] = new int[n]; // available colors

        if (d > maxDeg)
        {
            maxDeg = d;
            maxVer = i;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < graph[i][2][0]; j++)
        {
            int x;
            cin >> x;
            graph[i][3][j] = x;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][4][j] = -1; //-1 will mean that color is available

    color(maxVer);

    for (int i = 0; i < n; i++)
    {
        cout << "Vertex " << i << " Color " << graph[i][1][0];
        cout << endl;
    }

    // 3D graph test output
    // for (int i = 0; i < n; i++)
    // {
    //     for (int k = 0; k < graph[i][2][0]; k++)
    //     {
    //         cout << graph[i][3][k] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            delete[] graph[i][j];
        }
        delete[] graph[i];
    }
    delete[] graph;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}

// INPUT
// 15
// 3
// 3
// 4
// 2
// 3
// 4
// 3
// 3
// 1
// 2
// 3
// 2
// 2
// 2
// 1
// 1 2 3
// 0 4 5
// 0 6 7 8
// 0 9
// 1 5 10
// 1 4 11 12
// 2 7 13
// 2 6 14
// 2
// 3 10
// 4 9 11
// 5 10
// 5 13
// 6 12
// 7

// OUTPUT
// Vertex 0 Color 1
// Vertex 1 Color 0
// Vertex 2 Color 0
// Vertex 3 Color 0
// Vertex 4 Color 2
// Vertex 5 Color 1
// Vertex 6 Color 1
// Vertex 7 Color 2
// Vertex 8 Color 1
// Vertex 9 Color 1
// Vertex 10 Color 0
// Vertex 11 Color 2
// Vertex 12 Color 0
// Vertex 13 Color 2
// Vertex 14 Color 0