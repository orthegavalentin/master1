#ifndef COORD_H
#define COORD_H

#include <iostream>

class Coord
{
public:
    Coord();
    Coord(double x, double y, double z);

    double getX();
    double getY();
    double getZ();
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    bool equals(Coord* c);

private:
    double x, y, z;
};

std::ostream& operator<< (std::ostream& stream, Coord& c);
std::ostream& operator<< (std::ostream& stream, Coord*c);

#endif // COORD_H
