#include <bits/stdc++.h>

using namespace std;

int ***graph;
int *colors;
int n;
int finish = 0;
priority_queue<pair<int, int>> degree;

// graph[][0][0] == saturation
// graph[][1][0] == color
// graph[][2][0] == degree

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
    cin >> n;
    graph = new int **[n];
    colors = new int[n];
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
        graph[i][4] = new int[n]; // unavailable colors

        // degree.push({d, i});
        if (d > maxDeg)
        {
            maxDeg = d;
            maxVer = i;
        }

        colors[i] = i;
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
            graph[i][4][j] = -1;

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

    // priority queue test output
    // cout << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     int x = degree.top().first;
    //     int y = degree.top().second;
    //     degree.pop();
    //     cout << x << ' ' << y << endl;
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