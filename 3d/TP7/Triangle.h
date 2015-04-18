#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include <cmath>

class Triangle {
private:
  Point* p1;
  Point* p2;
  Point* p3;

  Point* v1;
  Point* v2;
  Point* v3;

  void computeNormals();
  ;
public:
  Triangle(Point* p1, Point* p2, Point* p3);
  void drawTriangle();
  void drawFace();
  void drawNormales();
  double minX();
  double maxX();
  double minY();
  double maxY();
  double minZ();
  double maxZ();
  std::vector<Point*> getNormales();
  std::vector<Point*> getPoints();
  void display();
};

void Triangle::display() {
  for (auto i : getPoints()) {
    std::cout << i;
  }
  std::cout << std::endl;
}

std::vector<Point*> Triangle::getNormales() {
  std::vector<Point*> v;
  v.push_back(v1);
  v.push_back(v2);
  v.push_back(v3);
  return v;
}

std::vector<Point*> Triangle::getPoints() {
  std::vector<Point*> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  return v;
}

void Triangle::computeNormals() {
  // std::cout << p1 << " " << p2 << " " << p3 << std::endl;
  Vector* n = p1->getNormale(p2, p3);
  v1 = new Point(n->getX() + p1->getX(), n->getY() + p1->getY(), n->getZ() + p1->getZ());
  v2 = new Point(n->getX() + p2->getX(), n->getY() + p2->getY(), n->getZ() + p2->getZ());
  v3 = new Point(n->getX() + p3->getX(), n->getY() + p3->getY(), n->getZ() + p3->getZ());
}

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
	computeNormals();
}

void Triangle::drawTriangle() {
  glBegin(GL_LINES);

  glColor3f(1, 0, 0);
  glVertex3f(p1->getX(), p1->getY(), p1->getZ());
  glVertex3f(p2->getX(), p2->getY(), p2->getZ());
  glColor3f(0, 1, 0);
  glVertex3f(p2->getX(), p2->getY(), p2->getZ());
  glVertex3f(p3->getX(), p3->getY(), p3->getZ());
  glColor3f(0, 0, 1);
  glVertex3f(p3->getX(), p3->getY(), p3->getZ());
  glVertex3f(p1->getX(), p1->getY(), p1->getZ());

  glEnd();
  glColor3f(1, 1, 1);
  // drawNormales();
}

void Triangle::drawFace() {
	glBegin(GL_TRIANGLES);

	glVertex3f(p1->getX(), p1->getY(), p1->getZ());
	glVertex3f(p2->getX(), p2->getY(), p2->getZ());
	glVertex3f(p3->getX(), p3->getY(), p3->getZ());
	
	glEnd();
	// drawNormales();
}

void Triangle::drawNormales() {
  // std::cout << "v1 : " << v1 << std::endl;
  // std::cout << "v2 : " << v2 << std::endl;
  // std::cout << "v3 : " << v3 << std::endl;
  glBegin(GL_LINES);
  glVertex3f(p1->getX(), p1->getY(), p1->getZ());
  glVertex3f(v1->getX(), v1->getY(), v1->getZ());
  glVertex3f(p2->getX(), p2->getY(), p2->getZ());
  glVertex3f(v2->getX(), v2->getY(), v2->getZ());
  glVertex3f(p3->getX(), p3->getY(), p3->getZ());
  glVertex3f(v3->getX(), v3->getY(), v3->getZ());
  glEnd();
}

#endif
