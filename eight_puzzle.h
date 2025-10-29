#pragma once

class Node {
    public:
        Node* parent;
        Node* left;
        Node* right;
        int value;

        //ctor
        Node() : parent(nullptr), left(nullptr), right(nullptr), value(0) {}
        Node(int num) : parent(nullptr), left(nullptr), right(nullptr), value(num) {}
        ~Node() {}
};

class Tree {
    public:
    Node* root;

    //ctor
    Tree() : root(nullptr) {}

    // functions
    void addNode(int);
    void removeNode(int);
    void drawPath();
    int getNodeCount();
};