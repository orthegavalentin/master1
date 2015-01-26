#ifndef VECTOR_H
#define VECTOR_H

#include "coord.h"
#include <math.h>

class Vector : public Coord
{
public:
    Vector();
    Vector(double x, double y, double z);
    Vector(Coord *p2, Coord *p1);

    double getNorme();
    void normalize();
    double scalar(Vector* vector2);
    Vector *vectoriel (Vector *vector2);
    double getAngle(Vector* vector2);

};

#endif // VECTOR_H
