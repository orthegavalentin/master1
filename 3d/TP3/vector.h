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
    void mul(float);
    double scalar(Vector* vector2);
    Vector *vectoriel (Vector *vector2);
    double getAngle(Vector* vector2);
    void add(Vector*);

};

#endif // VECTOR_H
