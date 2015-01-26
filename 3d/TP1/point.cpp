#include "point.h"

Point::Point()
{
}

Point::Point(double x, double y, double z) : Coord(x, y, z)
{

}

Point *Point::projectOnLine(Point *b, Point *c)
{
    Vector u(b, c);
    std::cout << "u : " << u << std::endl;
    return this->projectOnLine(&u, b);
}

Point *Point::projectOnLine(Vector *u, Point *b)
{
    Point *a = this;
    Vector ba(b, a);

    double norme = ba.scalar(u) / u->getNorme();
    return new Point(b->getX() + u->getX() * norme,
                     b->getY() + u->getY() * norme,
                     b->getZ() + u->getZ() * norme);
}

Point *Point::projectOnPlan(Point *a, Vector *n)
{
    Point *m = this;
    Vector ma(a, m);

    double norme = ma.scalar(n) / n->getNorme();

    return new Point(m->getX() - n->getX() * norme,
                     m->getY() - n->getY() * norme,
                     m->getZ() - n->getZ() * norme);
}
