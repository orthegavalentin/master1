#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <stdlib.h>

#include "heap.h"

using namespace std;

class node {
public:
    float weight;
    long value;
    bool valueInt;
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
    string convertToString(vector<int>* v);
    vector<int> convertToChars(vector<bool> v);

private:
    vector<node*> s;
    map<string, string>* charToBits;
    map<string, string>* bitsToChar;
    map<long, int>* m;
    node* parent;
    void compute();
    void display();
    void explore(node* n);
    float total;
    float number;
    Heap<node*>* h;
    //map<long, string> *m
};

#endif // HUFFMAN_H
