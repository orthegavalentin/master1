#include "point.h"
#include "vector.h"
#include <iostream>

int main() {
    Point* a = new Point(2, 1, 0);
    Point* b = new Point(4, 1, 0);
    Point* c = new Point(3.5, 3.5, 0);

    std::cout << c->projectOnLine(a, b) << std::endl;

    Point *a1 = new Point(0, 0, 0);
    Vector *n = new Vector(0, 0, 1);
    Point *m = new Point(1, 1, 1);

    std::cout << m->projectOnPlan(a1, n) << std::endl;
}
