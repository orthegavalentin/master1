#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include "heap.h"

using namespace std;

class node {
public:
    float weight;
    long value;
    string code;
    node* left = nullptr;
    node* right = nullptr;
    node(long value, float weight, node *left, node *right);

    bool operator< (const node& n) const
    {
        return (weight < n.weight);
    }
};

class Huffman
{
public:
    Huffman();
    Huffman(map<long, int> *m);


private:
    vector<node*> s;
    node* parent;
    void compute();
    void display();
    string explore(node* n);
    float total;
    float number;
    Heap<node*>* h;
    //map<long, string> *m
};

#endif // HUFFMAN_H
