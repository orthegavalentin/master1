#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

template<typename Type>
class Heap
{
public:
        Heap(int s);
        void add(Type v);
        void pop();
        Type top();
        void display();
        Type *sort();
        int size() const;

    private:
        int s;
        Type* heap;

        void up();
        int father(int i);
        int leftSon(int i);
        int rightSon(int i);
        bool fatherGreater(int i);
        void switchWithFather(int i);
        void down();
        int smallerSon(int i);
};

template<typename Type>
Heap<Type>::Heap(int size)
{
    heap = new Type[size];
    this->s = 1;
}

template<typename Type>
int Heap<Type>::father(int i)
{
    if(i/2 < 1) {
        return 1;
    }
    return i/2;
}

template<typename Type>
int Heap<Type>::leftSon(int i)
{
    return i*2;
}

template<typename Type>
int Heap<Type>::rightSon(int i)
{
    return i*2+1;
}

template<typename Type>
bool Heap<Type>::fatherGreater(int i)
{
    return *heap[i] < *heap[father(i)];
}

template<typename Type>
void Heap<Type>::switchWithFather(int i)
{
    Type temp = heap[i];
    heap[i] = heap[father(i)];
    heap[father(i)] = temp;
}

template<typename Type>
void Heap<Type>::up()
{
    for (int i = s; i > 0; i /= 2)
    {
        if(fatherGreater(i))
        {
            switchWithFather(i);
        }
        else
        {
            return;
        }
    }
}

template<typename Type>
void Heap<Type>::add(Type v)
{
    heap[s] = v;
    up();
    s++;
}

template<typename Type>
int Heap<Type>::smallerSon(int i)
{
    if(rightSon(i) > s)
    {
        return leftSon(i);
    }

    if(*heap[leftSon(i)] < *heap[rightSon(i)])
    {
        return leftSon(i);
    }
    else
    {
        return rightSon(i);
    }
}

template<typename Type>
void Heap<Type>::down()
{
    bool b = true;
    int i = 1;

    while(b)
    {
        b = false;

        int ss = smallerSon(i);

        if(ss > s)
            return;

        if(*heap[ss] < *heap[i])
        {
            switchWithFather(ss);
            b = true;
            i = ss;
        }
    }
}

template<typename Type>
void Heap<Type>::pop()
{
    s--;
    heap[1] = heap[s];
    down();
}

template<typename Type>
Type Heap<Type>::top()
{
    return heap[1];
}

template<typename Type>
Type* Heap<Type>::sort()
{
    Type* sorted = new Type[s];
    int n = s;

    for (int i = 0; i < n-1; ++i)
    {
        sorted[i] = top();
        std::cout << top()->weight << std::endl;
        pop();

    }
    return sorted;
}

template<typename Type>
int Heap<Type>::size() const
{
    return s - 1;
}

template<typename Type>
void Heap<Type>::display()
{
    for (int i = 1; i < s; i++)
    {
        std::cout << heap[i]->value << "  ";
    }
    std::cout << std::endl;
}

#endif // HEAP_H
