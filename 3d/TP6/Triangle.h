#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle {
public:
	Point* p1;
	Point* p2;
	Point* p3;

	Triangle(Point* p1, Point* p2, Point* p3);
	void drawTriangle();

};

Triangle::Triangle(Point* p1, Point* p2, Point* p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

void Triangle::drawTriangle() {
	glBegin(GL_LINES);
	
	glVertex3f(p1->getX(), p1->getY(), p1->getZ());
	glVertex3f(p2->getX(), p2->getY(), p2->getZ());
	glVertex3f(p3->getX(), p3->getY(), p3->getZ());
	
	glEnd();
}

#endif