#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>

using namespace std;

int ***graph;
int *colors;
int n;
int finish;
priority_queue<pair<int, int>> degree;

// graph[][0][0] == saturation
// graph[][1][0] == color
// graph[][2][0] == degree

int max_sat()
{
    // int maxSat = -1;
    // int maxVertex = -1;

    // for (int i = 0; i < n; i++)
    // {
    //     if (graph[i][0][0] > maxSat && graph[i][1][0] == -1)
    //     {
    //         maxSat = graph[i][0][0];
    //         maxVertex = i;
    //     }
    // }
    // return maxVertex;
    int maxSat = 0;
    for (int i = 0; i < n; i++)
    {
        if ((graph[i][0][0] >= graph[maxSat][0][0]) && graph[i][1][0] == -1)
        {
            if (graph[i][2][0] > graph[maxSat][2][0])
                maxSat = i;
        }
    }
    return maxSat;
}

void color(int v)
{
    priority_queue<int, vector<int>, greater<int>> usedColors;
    usedColors.push(-1);

    for (int i = 0; i < graph[v][2][0]; i++)
    {
        int neighbor = graph[v][3][i];
        if (graph[neighbor][1][0] != -1)
            usedColors.push(graph[neighbor][1][0]);
        graph[neighbor][0][0]++;
    }

    if (usedColors.top() != 0)
        graph[v][1][0] = 0;
    else
    {
        usedColors.pop();
        for (int i = 1; i < n; i++)
        {
            int num = usedColors.top();
            usedColors.pop();
            if (i != num)
                graph[v][1][0] = i;
            if (usedColors.empty())
                graph[v][1][0] = i++;
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

    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;

        graph[i] = new int *[4];
        graph[i][0] = new int[1];
        graph[i][1] = new int[1];
        graph[i][2] = new int[1];
        graph[i][3] = new int[d];

        graph[i][0][0] = 0;
        graph[i][1][0] = -1;
        graph[i][2][0] = d;

        degree.push({d, i});

        for (int k = 0; k < d; k++)
        {
            int x;
            cin >> x;
            graph[i][3][k] = x;
        }
        colors[i] = i;
    }

    color(degree.top().second);

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
// 3 1 2 3
// 3 0 4 5
// 4 0 6 7 8
// 2 0 9
// 3 1 5 10
// 4 1 4 11 12
// 3 2 7 13
// 3 2 6 14
// 1 2
// 2 3 10
// 3 4 9 11
// 2 5 10
// 2 5 13
// 2 6 12
// 1 7
