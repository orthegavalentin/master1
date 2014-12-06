#include "huffman.h"

Huffman::Huffman()
{
}

Huffman::Huffman(map<long, int> *m)
{
    total = 0;
    maxOccurence = 0;
    number = m->size();
    this->m = m;
    charToBits = new map<string, string>;
    bitsToChar = new map<string, string>;
    float f = 0;

    for(const auto& e : *m) {
        total += e.first;
        if(e.second > maxOccurence) {
            maxOccurence = e.second;
        }
        if(e.first > maxOccurence) {
            maxOccurence = e.first;
        }
        //cout << "key : " << e.first << endl;
        //cout << "value : " << e.second << endl;
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
    string s1 = "";

    int encodingLength = ceil(log2(maxOccurence));
    cout << "encoding length for huffman : " << encodingLength << endl;

    bitset<8> bit(encodingLength);
    bit[7] = 1;

    s += bit.to_string();

    for(const auto& e : *m) {
        s += intToBitString(encodingLength, e.first);
        s += intToBitString(encodingLength, e.second);
    }

    int n = 8 - s.size() % 8;
    for (int var = 0; n < 8 && var < n; ++var) {
        s += "1";
    }
    cout << "[convertToString] extra data : " << n << endl;

    s += std::bitset<24>(0).to_string();
    cout << "dico size : " << s.size() << endl;
    //cout << "[convertToString] dico : " << s << endl;

    cout << "converting to string" << endl;
    for (int var = 0; var < v->size(); ++var) {
        s += charToBits->at(to_string(v->at(var)));
        s1 += charToBits->at(to_string(v->at(var)));
    }
    n = 8 - s.size() % 8;
    cout << "[convertToString] extra data : " << n << endl;
    for (int var = 0; n < 8 && var < n + 8; ++var) {
        s += "0";
    }
    cout << "converted" << endl;
    //cout << "[convertToString] data : " << s1 << endl;
    return s;
}

vector<int>* Huffman::convertToChars(vector<bool>* v)
{
    cout << "converting to chars " << endl;
    string current = "";
    vector<int>* vec = new vector<int>;
    node* n = parent;
    cout << "size : " << v->size() << endl;
    //cout << "[convertToChars] data : ";
    for (int var = 0; var < v->size(); ++var) {
        if(n->left == nullptr) {
            vec->push_back(n->value);
            n = parent;
            current = "";
        }
        if(v->at(var) == n->left->valueInt) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    cout << endl;
    vec->push_back(0);
    //vec->erase(vec->begin() + vec->size() - 1);
    for(const auto& e : *vec) {
        //cout << "[convertToChars] vec : " << e << endl;
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

        //cout << "value = " << n->value << " : " << n->code << endl;
        charToBits->insert(std::pair<string, string>(to_string(n->value), n->code));
        bitsToChar->insert(std::pair<string, string>(n->code, to_string(n->value)));
        return;
    }
    n->right->code = n->code + n->right->code;
    n->left->code = n->code + n->left->code;
    explore(n->right);
    explore(n->left);
}

string Huffman::intToBitString(int size, int n)
{
    bitset<512> bit(n);
    string s = "";
    for (int var = 0; var < size; ++var) {
        s += to_string(bit[size - var - 1]);
    }
    return s;
}


node::node(long value, float weight, node *left, node *right)
{
    this->value = value;
    this->weight = weight;
    this->left = left;
    this->right = right;
}
