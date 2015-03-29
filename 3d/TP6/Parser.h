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

private:
	std::vector<double> getBounds(std::vector<Triangle*> triangles);
};

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
			// std::cout << coords[coords.size() - 1] << std::endl;
		} else {
			int a, x, y, z;
			if (!(i >> a >> x >> y >> z)) { 
				break; 
			}
			// std::cout << x << y << z << std::endl;
			triangles.push_back(new Triangle(coords[x], coords[y], coords[z]));
		}
	}

	glColor3f(1.0, 1.0, 1.0);

	for(auto t : triangles) {
		t->drawTriangle();
	}
	return triangles;
}

#endif