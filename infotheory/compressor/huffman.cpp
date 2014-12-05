#include "huffman.h"

Huffman::Huffman()
{
}

Huffman::Huffman(map<long, int> *m)
{
    total = 0;
    number = m->size();
    this->m = m;
    charToBits = new map<string, string>;
    bitsToChar = new map<string, string>;
    float f = 0;

    for(const auto& e : *m) {
        total += e.first;
        //cout << "key : " << e.first << endl;
        //cout << "value : " << e.second  << endl;
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

string Huffman::convertToString(vector<int> *v)
{
    string s = "";
    int first = 0;
    string s1 = "";
    for(const auto& e : *m) {
        if(first == 0) {
            first = e.first + pow(2, 11);
            s += std::bitset<12>(first).to_string();
        } else {
            s += std::bitset<12>(e.first).to_string();
        }
        s += std::bitset<12>(e.second).to_string();
    }
    s += std::bitset<16>(0).to_string();

    cout << "dico : " << s << endl;

    cout << "dico size : " << s.size() << endl;
    cout << "extra : " << s.size() % 8 << endl;

    cout << "converting to string" << endl;
    for (int var = 0; var < v->size(); ++var) {
        //cout << to_string(v->at(var)) << endl;
        cout << to_string(v->at(var)) << endl;
        s += charToBits->at(to_string(v->at(var)));
        s1 += charToBits->at(to_string(v->at(var)));
    }
    cout << "converted" << endl;
    cout << "data : " << s1 << endl;
    return s;
}

vector<int> Huffman::convertToChars(vector<bool>* v)
{
    cout << "converting to chars " << endl;
    string current = "";
    vector<int> vec;
    node* n = parent;
    for (int var = 0; var < v->size(); ++var) {
        cout << v->at(var);
        if(n->left == nullptr) {
            //cout << n->code << endl;
            //cout << "value = " << n->value << " : " << n->code << endl;
            vec.push_back(n->value);
            n = parent;
            current = "";

        }
        if(v->at(var) == n->left->valueInt) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    for(const auto& e : vec) {
        cout << e << endl;
    }
    return vec;
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
        n1->valueInt = 1;
        n2->code = "0";
        n2->valueInt = 0;
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

void Huffman::explore(node *n)
{
    if(n->left == nullptr) {
        total += n->code.size();
        cout << "value = " << n->value << " : " << n->code << endl;
        charToBits->insert(std::pair<string, string>(to_string(n->value), n->code));
        bitsToChar->insert(std::pair<string, string>(n->code, to_string(n->value)));
        return;
    }
    n->right->code = n->code + n->right->code;
    n->left->code = n->code + n->left->code;
    explore(n->right);
    explore(n->left);
}


node::node(long value, float weight, node *left, node *right)
{
    this->value = value;
    this->weight = weight;
    this->left = left;
    this->right = right;
}
