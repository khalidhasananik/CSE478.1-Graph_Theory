#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    int n;
    vector<vector<int>> adj;
    vector<int> sat;
    vector<int> col;

    Graph(int n) : n(n)
    {
        adj.resize(n);
        col.resize(n);
        sat.resize(n);

        for (int i = 0; i < n; i++)
        {
            col[i] = -1;
            sat[i] = 0;
        }
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

class DoublyLinkedList
{
public:
    // Node structure
    struct Node
    {
        int data;
        Node *next; // Pointer to the next node
        Node *prev; // Pointer to the previous node
    };

private:
    Node *head; // Pointer to the head of the list

public:
    // Constructor
    DoublyLinkedList()
    {
        head = nullptr; // Initialize head to nullptr
    }

    // Destructor
    ~DoublyLinkedList()
    {
        while (head != nullptr)
        {
            deleteFront();
        }
    }

    // Insert a node at the front of the list
    void insertFront(int data)
    {
        Node *newNode = new Node();
        newNode->data = data;
        newNode->next = head;
        newNode->prev = nullptr;

        if (head != nullptr)
            head->prev = newNode;

        head = newNode;
    }

    // Insert a node at the end of the list
    // void insertEnd(int data)
    // {
    //     Node *newNode = new Node();
    //     newNode->data = data;
    //     newNode->next = nullptr;

    //     if (head == nullptr)
    //     {
    //         newNode->prev = nullptr;
    //         head = newNode;
    //         return;
    //     }

    //     Node *temp = head;
    //     while (temp->next != nullptr)
    //         temp = temp->next;

    //     temp->next = newNode;
    //     newNode->prev = temp;
    // }

    // Insert a node after a given node
    void insertAfter(Node *prevNode, int data)
    {
        if (prevNode == nullptr)
            return;

        Node *newNode = new Node();
        newNode->data = data;

        newNode->next = prevNode->next;
        prevNode->next = newNode;
        newNode->prev = prevNode;

        if (newNode->next != nullptr)
            newNode->next->prev = newNode;
    }

    // Insert a node before a given node
    void insertBefore(Node *nextNode, int data)
    {
        if (nextNode == nullptr)
            return;

        Node *newNode = new Node();
        newNode->data = data;
        newNode->next = nextNode;
        newNode->prev = nextNode->prev;

        if (nextNode->prev != nullptr)
            nextNode->prev->next = newNode;
        else
            head = newNode; // If inserting before the head, update the head pointer

        nextNode->prev = newNode;
    }

    // Delete the front node
    void deleteFront()
    {
        // if (head == nullptr)
        //     return;

        // Node *temp = head;
        // head = head->next;

        // if (head != nullptr)
        //     head->prev = nullptr;

        // delete temp;

        if (head == nullptr)
            return;

        Node *temp = head;

        // If there is only one node in the list
        if (head->next == nullptr)
            head = nullptr; // Update head to nullptr after deletion
        else
        {
            head = head->next; // Move head to the next node
            head->prev = nullptr;
        }

        delete temp;
    }

    // Delete the last node
    // void deleteEnd()
    // {
    //     if (head == nullptr)
    //         return;

    //     if (head->next == nullptr)
    //     {
    //         delete head;
    //         head = nullptr;
    //         return;
    //     }

    //     Node *temp = head;
    //     while (temp->next != nullptr)
    //         temp = temp->next;

    //     temp->prev->next = nullptr;
    //     delete temp;
    // }

    // Delete a specific node
    void deleteNode(Node *del)
    {
        if (head == nullptr || del == nullptr)
            return;

        if (head == del)
            head = del->next;

        if (del->next != nullptr)
            del->next->prev = del->prev;

        if (del->prev != nullptr)
            del->prev->next = del->next;

        delete del;
    }

    // Traverse the list forward
    void traverseForward()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Traverse the list backward
    // void traverseBackward()
    // {
    //     Node *temp = head;
    //     if (temp == nullptr)
    //         return;

    //     // Go to the last node
    //     while (temp->next != nullptr)
    //         temp = temp->next;

    //     // Traverse backward
    //     while (temp != nullptr)
    //     {
    //         cout << temp->data << " ";
    //         temp = temp->prev;
    //     }
    //     cout << endl;
    // }

    // Search for a node with a specific value
    // Node *search(int key)
    // {
    //     Node *temp = head;
    //     while (temp != nullptr)
    //     {
    //         if (temp->data == key)
    //             return temp;
    //         temp = temp->next;
    //     }
    //     return nullptr;
    // }

    // Get the head (used for other operations like inserting after or deleting a specific node)
    Node *getHead()
    {
        return head;
    }
};