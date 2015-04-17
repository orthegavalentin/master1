#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
#include "Triangle.h"

class Repere {
 public:
  double size;
  double x, y, z;

  Repere(std::vector<Triangle*> triangles);
  void gaussienne(std::vector<Triangle*> t);

 private:
  std::vector<double> getBounds(std::vector<Triangle*> triangles);
};

void Repere::gaussienne(std::vector<Triangle*> t) {
  glBegin(GL_LINES);
  Point p(x, y, z);
  for (auto triangle : t) {
    for (int i = 0; i < 3; i++) {
      std::vector<Point*> normales = triangle->getNormales();
      std::vector<Point*> points = triangle->getPoints();
      Vector v(normales[i], points[i]);
      v.mul(size / v.getNorme());
      glVertex3f(p.getX(), p.getY(), p.getZ());
      glVertex3f(v.getX() + p.getX(), v.getY() + p.getY(), v.getZ() + p.getZ());
    }
  }
  glEnd();

}

Repere::Repere(std::vector<Triangle*> triangles) {
  std::vector<double> bounds;
  bounds.push_back(triangles[0]->minX()); //min x
  bounds.push_back(triangles[0]->maxX()); //max x
  bounds.push_back(triangles[0]->minY()); //min y
  bounds.push_back(triangles[0]->maxY()); //max y
  bounds.push_back(triangles[0]->minZ());
  bounds.push_back(triangles[0]->maxZ());

  for(auto t : triangles) {
    bounds[0] = fmin(bounds[0], t->minX());
    bounds[1] = fmax(bounds[1], t->maxX());
    bounds[2] = fmin(bounds[2], t->minY());
    bounds[3] = fmax(bounds[3], t->maxY());
    bounds[4] = fmin(bounds[4], t->minZ());
    bounds[5] = fmax(bounds[5], t->maxZ());
  }

  double distX = bounds[1] - bounds[0];
  double distY = bounds[3] - bounds[2];
  double distZ = bounds[5] - bounds[4];

  this->size = fmax(distX, fmax(distY, distZ));

  distX = (this->size - distX) * 0.5f;
  bounds[0] -= distX;
  bounds[1] += distX;

  distY = (this->size - distY) * 0.5f;
  bounds[2] -= distY;
  bounds[3] += distY;

  distZ = (this->size - distZ) * 0.5f;
  bounds[4] -= distZ;
  bounds[5] += distZ;

  x = (bounds[1] + bounds[0]) * 0.5f;
  y = (bounds[3] + bounds[2]) * 0.5f;
  z = (bounds[5] + bounds[4]) * 0.5f;
}

std::vector<Triangle*> parseFile(std::string path) {
  std::ifstream f(path.c_str());

  std::string line;
  std::getline(f, line);
  std::getline(f, line);

  std::istringstream iss(line);

  int nbCoords;
  int nbTriangles;
  std::vector<Point*> coords;
  std::vector<Triangle*> triangles;

  iss >> nbCoords >> nbTriangles;

  long cpt = 0;

  while (std::getline(f, line)) {
    std::istringstream i(line);

    if(cpt++ < nbCoords) {
      double x, y, z;
      if (!(i >> x >> y >> z)) { 
	break; 
      }
      coords.push_back(new Point(x, y, z));
    } else {
      int a, x, y, z;
      if (!(i >> a >> x >> y >> z)) { 
	break; 
      }
      triangles.push_back(new Triangle(coords[x], coords[y], coords[z]));
    }
  }

  glColor3f(1.0, 1.0, 1.0);

  for(auto t : triangles) {
    t->drawTriangle();
  }
  return triangles;
}


std::vector<Triangle*> maillageCylindre(Point* orig, int radius, int height, int meridians) {
  Point*** c = cylindre(orig, radius, height, meridians);
  std::vector<Triangle*> triangles;

  for (int i = 0; i < meridians; ++i) {
    triangles.push_back(new Triangle(c[0][i], c[0][(i+1)%meridians], c[1][(i+1)%meridians]));
  }

  for (int i = 0; i < meridians; ++i) {
    triangles.push_back(new Triangle(c[0][(i)%meridians], c[1][(i+1)%meridians], c[1][i]));
  }

  for (int i = 1; i < meridians; ++i) {
    // triangles.push_back(new Triangle(c[0][i], c[0][0], c[0][(i+1)%meridians]));
    // triangles.push_back(new Triangle(c[1][i], c[1][(i+1)%meridians], c[1][0]));
  }

  return triangles;
}

std::vector<Triangle*> maillageSphere(Point* orig, int radius, int meridians, int parallels) {
  Point*** c = sphere(orig, radius, meridians, parallels);
  std::vector<Triangle*> triangles;

  for (int j = 0; j < parallels; j++) {
    for (int i = 0; i < meridians; i+=2) {
      triangles.push_back(new Triangle(c[i][j], c[i][(j+1)%parallels], c[(i+1)%meridians][j]));
      triangles.push_back(new Triangle(c[i][(j+1)%parallels], c[(i+1)%meridians][(j+1)%parallels], c[(i+1)%meridians][j]));
    }
  }

  return triangles;
}

bool neighbours (Triangle* t1, Triangle* t2) {
  int n = 0;
  for (auto i : t1->getPoints()) {
    for (auto j : t2->getPoints()) {
      n += i->equals(j);
    }
  }
  return n == 2;
}

bool diedre (Triangle* t1, Triangle* t2, double a) {
  double angle = 1 - a;
  Point* n1 = t1->getNormales()[0];
  Point* n2 = t2->getNormales()[0];
  // if(neighbours(t1, t2)) {
    Vector v1(n1->getX(), n1->getY(), n1->getZ());
    Vector v2(n2->getX(), n2->getY(), n2->getZ());
    std::cout << v1.getAngle(&v2) << std::endl;
    return (v1.getAngle(&v2) < angle);
  // }
  return false;
}

std::vector<std::vector<Triangle*>> matriceAdjacence(std::vector<Triangle*> triangles) {
  std::vector<std::vector<Triangle*>> matrix;
  for (int i = 0; i < triangles.size(); i++) {
    std::vector<Triangle*> t;
    matrix.push_back(t);
    for (int j = i; j < triangles.size(); j++) {
      if(neighbours(triangles[i], triangles[j])) {
	matrix[i].push_back(triangles[j]);
      }
    }
  }
  return matrix;
}

std::vector<Triangle*> getDiedres(std::vector<std::vector<Triangle*>> matrix, double angle) {
  std::vector<Triangle*> triangles;
  for (auto i : matrix) {
    if(i.size() > 0) {
      for (int j = 0; j < i.size(); j++) {
	for (int k = j; k < i.size(); k++) {
	  if(diedre(i[j], i[k], angle)) {
	    triangles.push_back(i[j]);
	    triangles.push_back(i[k]);	    
	  }
	}
      }
    }
  }
	      return triangles;
}

#endif







