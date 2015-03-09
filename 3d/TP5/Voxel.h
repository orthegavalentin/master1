#ifndef VOXEL_H
#define VOXEL_H

#include "opengl.h"

class Voxel {
public:
	Voxel(Point* orig, double size);
	void draw();

private:
	Point*** sommets;
	double size;
	Point* orig;
};

//orig = bas gauche front
Voxel::Voxel(Point* orig, double size) {
	sommets = new Point**[2];
	for (int i = 0; i < 2; ++i) {
		sommets[i] = new Point*[4];
	}

	Point p(orig->getX() - size * 0.5f, orig->getY() - size * 0.5f, orig->getZ() - size * 0.5f);

	sommets[0][0] = new Point(p.getX(), p.getY(), p.getZ());
	sommets[0][1] = new Point(p.getX(), p.getY() + size, p.getZ());
	sommets[0][2] = new Point(p.getX() + size, p.getY() + size, p.getZ());
	sommets[0][3] = new Point(p.getX() + size, p.getY(), p.getZ());
	sommets[1][0] = new Point(p.getX(), p.getY(), p.getZ() + size);
	sommets[1][3] = new Point(p.getX() + size, p.getY(), p.getZ() + size);
	sommets[1][1] = new Point(p.getX(), p.getY() + size, p.getZ() + size);
	sommets[1][2] = new Point(p.getX() + size, p.getY() + size, p.getZ() + size);

	this->size = size;
	this->orig = orig;
}

void Voxel::draw() {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
			glVertex3f(sommets[i][j%4]->getX(), sommets[i][j%4]->getY(), sommets[i][j%4]->getZ());
		}	
	}
	glEnd();

	glBegin(GL_LINES);
	for (int j = 0; j < 10; j+=3) {
		for (int i = 0; i < 2; ++i) {
			glVertex3f(sommets[i][j%4]->getX(), sommets[i][j%4]->getY(), sommets[i][j%4]->getZ());
		}	
	}
	glEnd();
}

void displaySphereVolumic(Point* orig, double rayon, double resolution, double step) {
	double size = ((M_PI / 2) * sqrt(2) * rayon / 2.0);
	Voxel v(orig, size);
	v.draw();
	if(step < resolution) {
		step++;
		displaySphereVolumic(new Point(orig->getX() + rayon - rayon / 4, orig->getY(), + orig->getZ()), rayon / 4, resolution, step);

		for (int i = 1; i < 4; ++i)
		{
			double m = (i % 2) * rayon / 4; if(i == 1) m *= -1;
			std::cout << m << std::endl;

			for (int j = 1; j < 4; ++j)
			{
				double n = (i % 2) * rayon / 4; if(i == 1) n *= -1;
				displaySphereVolumic(new Point(orig->getX() + rayon - rayon / 4, orig->getY() + m, + orig->getZ() + n), rayon / 4, resolution, step);
			}
		}
	}
}

#endif