#include "vector.h"

Vector::Vector()
{
}

Vector::Vector(double x, double y, double z) : Coord(x, y, z)
{

}

Vector::Vector(Coord *p1, Coord *p2) : Coord(p2->getX() - p1->getX(), p2->getY() - p1->getY(), p2->getZ() - p1->getZ())
{

}

double Vector::getNorme()
{
    return sqrt(this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ());
}

void Vector::normalize()
{
    double norme = getNorme();
    this->setX(this->getX() / norme);
    this->setY(this->getY() / norme);
    this->setZ(this->getZ() / norme);
}

double Vector::scalar(Vector *vector2)
{
    return this->getX() * vector2->getX() + this->getY() * vector2->getY() + this->getZ() + vector2->getZ();
}

Vector *Vector::vectoriel(Vector* vector2)
{
    return new Vector(this->getY() * vector2->getZ() - this->getZ() * vector2->getY(),
                      this->getZ() * vector2->getX() - this->getX() * vector2->getZ(),
                      this->getX() * vector2->getY() - this->getY() * vector2->getX());
}

double Vector::getAngle(Vector* vector2)
{
    return acos(this->scalar(vector2)/(this->getNorme() * vector2->getNorme()));
}
