#include "classes.cpp"

void dSatur(Graph &g)
{
    int n = g.n;
    int maxSat = 0;
    vector<int> deg(n);    // Degree of each vertex
    vector<int> pos(n);    // Position array
    vector<int> vert(n);   // Vertex array
    vector<int> colors(n); // All available colors
    vector<vector<bool>> takenCols(n, vector<bool>(n, false));
    DoublyLinkedList dll;
    vector<DoublyLinkedList::Node *> nodeLocator(n);
    vector<DoublyLinkedList::Node *> guideNode(n);

    for (int i = 0; i < n; i++)
    {
        deg[i] = g.adj[i].size();
        colors[i] = i;
    }

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

    // for (int d = 0; d < md; d++)
    //     bin[d] = bin[d + 1];
    // bin[md] = 0;

    // Ver: 2  5  0  1  4  6  7  10  3  9  11  12  13  8  14
    // Pos: 2  3  0  8  4  1  5  6  13  9  7  10  11  12  14
    // Deg: 3  3  4  2  3  4  3  3  1  2  3  2  2  2  1

    // Algorithm:
    // {-select a node
    //  -check available colors
    //  -color it with the minimum color
    //  -update saturation of neighbors
    //  -select next node with max saturation}
    // repeat

    for (int i = n - 1; i >= 0; i--)
    {
        dll.insertFront(vert[i]);
        nodeLocator[i] = dll.getHead();
    }

    guideNode[0] = dll.getHead();

    while (dll.getHead() != nullptr)
    {
        int v = dll.getHead()->data;
        if (guideNode[g.sat[v]]->data == nodeLocator[pos[v]]->data) // If a guide node is colored
        {
            guideNode[g.sat[v]] = guideNode[g.sat[v]]->next;
            maxSat -= 1;
        }
        dll.deleteFront();

        if (g.adj[v].size() == 0)
        {
            g.col[v] = 0;
            continue;
        }

        for (int i = 0; i < g.adj[v].size(); i++)
        {
            int neighbor = g.adj[v][i];
            if (g.col[neighbor] == -1)
            {
                if (guideNode[g.sat[neighbor]]->data == nodeLocator[pos[neighbor]]->data) // If saturation of guide node changes
                    guideNode[g.sat[neighbor]] = guideNode[g.sat[neighbor]]->prev;        // Move the guide node to the previous node

                g.sat[neighbor] += 1;

                dll.deleteNode(nodeLocator[pos[neighbor]]);

                if (g.sat[neighbor] > maxSat)
                {
                    maxSat = g.sat[neighbor];
                    dll.insertFront(neighbor);
                    guideNode[maxSat] = dll.getHead();
                    nodeLocator[pos[neighbor]] = dll.getHead();
                }
                else
                {
                    dll.insertBefore(guideNode[g.sat[neighbor]], neighbor);
                    nodeLocator[pos[neighbor]] = guideNode[g.sat[neighbor]]->prev;
                }
            }
            else
            {
                takenCols[v][g.col[neighbor]] = true;
            }
        }
        int x = 0;
        while (takenCols[v][x])
            x++;
        g.col[v] = x;
    }
}

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

    for (int i = 0; i < n; i++)
        cout << "Vertex " << i << ": " << g.col[i] << endl;

    return 0;
}
