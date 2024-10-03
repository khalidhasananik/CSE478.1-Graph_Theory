#include <bits/stdc++.h>
#define maxNodes 100000

using namespace std;

vector<int> graph[maxNodes];  // Adjacency list representation
int deg[maxNodes];
int sat[maxNodes];       
int colors[maxNodes];           
bool availableColors[maxNodes]; 

int findMaxSatVertex(int n)
{
    int maxSat = -1;
    int maxDeg = -1;
    int selectedVertex = -1;

    for (int i = 0; i < n; ++i)
    {
        if (colors[i] == -1)
        { 
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

void updateSat(int vertex)
{
    for (int neighbor : graph[vertex])
    {
        if (colors[neighbor] == -1)
        { // If it's a neighbor and uncolored
            unordered_set<int> neighborColors;

            // Check all neighbors of this neighbor
            for (int adj : graph[neighbor])
            {
                if (colors[adj] != -1)
                {
                    neighborColors.insert(colors[adj]);
                }
            }

            // Update saturation with the number of distinct colors
            sat[neighbor] = neighborColors.size();
        }
    }
}

void dsatur(int n)
{
    for (int i = 0; i < n; ++i)
    {
        colors[i] = -1;
        sat[i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        int vertex = findMaxSatVertex(n);

        fill(availableColors, availableColors + n, true); 

        for (int neighbor : graph[vertex])
        {
            if (colors[neighbor] != -1)
            {
                availableColors[colors[neighbor]] = false;
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
        updateSat(vertex);
    }
}

int main()
{
    string filename = "/home/kingpin/CSE478.1-Graph_Theory/EBBkC/src/graph_data.txt";
    ifstream inputFile(filename);

    if (!inputFile)
    {
        cerr << "Error opening file";
        return 1;
    }

    ofstream outputFile("graph_output.txt"); 

    if (!outputFile)
    {
        cerr << "Error with Output File";
        return 1;
    }

    int n = 0; 
    int u, v;

    while (inputFile >> u >> v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[u]++;
        deg[v]++;

        n = max(n, max(u, v) + 1);
    }

    inputFile.close();

    dsatur(n);

    int maxColor = 0;
    for (int i = 0; i < n; ++i)
    {
        maxColor = max(maxColor, colors[i]);
    }

    // Output the color of each vertex to the file
    outputFile << "Vertex colors:" << endl;
    for (int i = 0; i < n; ++i)
    {
        outputFile << "Vertex " << i << ": Color " << colors[i] << endl;
    }

    outputFile << "Maximum Number of Colors Needed: " << maxColor + 1 << endl;

    outputFile.close();  // Close the output file

    cout << "Output has been generated" << endl;

    return 0;
}


