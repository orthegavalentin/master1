#include "huffman.h"

Huffman::Huffman()
{
}

Huffman::Huffman(map<long, int> *m)
{
    total = 0;
    number = m->size();
    float f = 0;

    for(const auto& e : *m) {
        total += e.first;
    }
    h = new Heap<node*>(m->size() * 2);
    for(const auto& e : *m) {
        f += e.second/total * log2(e.second/total);
        node* n = new node(e.first, e.second, 0, 0);
        h->add(n);
    }
    total = 0;
    compute();
    cout << "total : " << m->size() << endl;
    display();
}

void Huffman::compute()
{
    cout << endl;
    while(h->size() > 1) {
        node* n1 = h->top();
        h->pop();
        node* n2 = h->top();
        h->pop();
        n1->code = "1";
        n2->code = "0";
        node* n = new node(0, n1->weight + n2->weight, n1, n2);
        h->add(n);
    }
    parent = h->top();
}

void Huffman::display()
{
    explore(parent);
    cout << "average huffman code size : " << total/number << endl;
}

string Huffman::explore(node *n)
{
    if(n->left == nullptr) {
        total += n->code.size();
        //cout << to_string(n->value) << " : " << n->code << endl;
        return "";
    }
    n->right->code = n->code + n->right->code;
    n->left->code = n->code + n->left->code;
    explore(n->right);
    explore(n->left);
    return "";
}


node::node(long value, float weight, node *left, node *right)
{
    this->value = value;
    this->weight = weight;
    this->left = left;
    this->right = right;
}
