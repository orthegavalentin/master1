#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
#include "Triangle.h"

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