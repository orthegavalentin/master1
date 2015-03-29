#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include <cmath>

class Triangle {
public:
	Point* p1;
	Point* p2;
	Point* p3;

	Triangle(Point* p1, Point* p2, Point* p3);
	void drawTriangle();
	double minX();
	double maxX();
	double minY();
	double maxY();
	double minZ();
	double maxZ();
};

double Triangle::minX() {
	double m = p1->getX();
	m = fmin(m, p2->getX());
	m = fmin(m, p3->getX());
	return m;	
}

double Triangle::maxX() {
	double m = p1->getX();
	m = fmax(m, p2->getX());
	m = fmax(m, p3->getX());
	return m;	
}

double Triangle::minY() {
	double m = p1->getY();
	m = fmin(m, p2->getY());
	m = fmin(m, p3->getY());
	return m;	
}

double Triangle::maxY() {
	double m = p1->getY();
	m = fmax(m, p2->getY());
	m = fmax(m, p3->getY());
	return m;	
}

double Triangle::minZ() {
	double m = p1->getZ();
	m = fmin(m, p2->getZ());
	m = fmin(m, p3->getZ());
	return m;	
}

double Triangle::maxZ() {
	double m = p1->getZ();
	m = fmax(m, p2->getZ());
	m = fmax(m, p3->getZ());
	return m;	
}


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