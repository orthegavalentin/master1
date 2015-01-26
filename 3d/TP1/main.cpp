#include "point.h"
#include "vector.h"
#include <iostream>

int main() {
    Point* a = new Point(2, 1, 0);
    Point* b = new Point(4, 1, 0);
    Point* c = new Point(3.5, 3.5, 0);

    std::cout << c->projectOnLine(a, b) << std::endl;

    Vector *v = new Vector(5, -2, 0);
    Vector *v2 = new Vector(7, -6, 0);

    std::cout << v->scalar(v2) << std::endl;
}
