#include "coord.h"

Coord::Coord()
{
}

Coord::Coord(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Coord::getX()
{
    return x;
}

double Coord::getY()
{
    return y;
}

double Coord::getZ()
{
    return z;
}

void Coord::setX(double x)
{
    this->x = x;
}

void Coord::setY(double y)
{
    this->y = y;
}

void Coord::setZ(double z)
{
    this->z = z;
}

bool Coord::equals(Coord* c) {
  return (this->getX() == c->getX() && this->getY() == c->getY() && this->getZ() == c->getZ());
}

std::ostream& operator<<(std::ostream& stream, Coord& c) {
    stream << "[" << c.getX() << ", " << c.getY() << ", " << c.getZ() << "]";
    return stream;
 }

std::ostream& operator<<(std::ostream& stream, Coord* c) {
    stream << "[" << c->getX() << ", " << c->getY() << ", " << c->getZ() << "]";
    return stream;
 }
