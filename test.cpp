#include <bits/stdc++.h>
#include "dll.cpp"

using namespace std;

int main()
{
    DoublyLinkedList dll;

    // Inserting elements
    dll.insertFront(10);
    dll.insertFront(5);

    DoublyLinkedList::Node *node = dll.getHead();

    vector<DoublyLinkedList::Node *> nodePointer;

    nodePointer.push_back(dll.getHead());

    dll.insertBefore(node, 12);

    cout << nodePointer[0]->data << endl;

    cout << nodePointer.size() << endl;

    // Deleting the front and the end nodes
    dll.deleteFront();

    return 0;
}
