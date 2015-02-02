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
    return this->projectOnLine(&u, b);
}

Point *Point::projectOnLine(Vector *u, Point *b)
{
    Point *a = this;
    Vector ba(a, b);

    u->normalize();

    double norme = ba.scalar(u);

    return new Point(b->getX() + u->getX() * norme,
                     b->getY() + u->getY() * norme,
                     b->getZ() + u->getZ() * norme);
}

Point *Point::projectOnPlan(Point *a, Vector *n)
{
    Point *m = this;
    Vector ma(m, a);

    n->normalize();

    double norme = ma.scalar(n);

    return new Point(m->getX() - n->getX() * norme,
                     m->getY() - n->getY() * norme,
                     m->getZ() - n->getZ() * norme);
}
