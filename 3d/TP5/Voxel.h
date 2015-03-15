#ifndef VOXEL_H
#define VOXEL_H

#include "opengl.h"
#include <vector>

class Voxel {
public:
	Voxel(Point* orig, double size);
	~Voxel();
	void draw();
	Voxel** subdivide();
	int intersectsSphere(Point* orig, double rayon);
	int intersectsCylindre(Point* orig, Vector* direction, double rayon);
	Point* orig;

private:
	Point*** sommets;
	double size;
};

//orig = bas gauche front
Voxel::~Voxel() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			delete(sommets[i][j]);
		}	
	}
	delete orig;
}

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
	glColor3f(1.0, 0.0, 0.0);
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

	/**
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
			glVertex3f(sommets[i][j%4]->getX(), sommets[i][j%4]->getY(), sommets[i][j%4]->getZ());
		}	
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int j = 0; j < 10; j+=3) {
		for (int i = 0; i < 2; ++i) {
			glVertex3f(sommets[i][j%4]->getX(), sommets[i][j%4]->getY(), sommets[i][j%4]->getZ());
		}	
	}
	glEnd();//*/
}

Voxel** Voxel::subdivide() {
	Voxel **p = new Voxel*[8];
	int cpt = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			Vector v(this->sommets[i][j]->getX() + orig->getX(), this->sommets[i][j]->getY() + orig->getY(), this->sommets[i][j]->getZ() + orig->getZ());
			v.mul(0.5f);
			p[cpt++] = new Voxel(new Point(v.getX(), v.getY(), v.getZ()), size * 0.5f);
		}	
	}
	return p;
}

int Voxel::intersectsSphere(Point* orig, double rayon) {
	int n = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			Vector v(this->sommets[i][j]->getX() - orig->getX(), this->sommets[i][j]->getY() - orig->getY(), this->sommets[i][j]->getZ() - orig->getZ());
			if(v.getNorme() > rayon) {
				n++;
			}
		}	
	}
	return n;
}

void stepSphere(Voxel *v, Point *orig, double rayon, double resolution, double iter) {
	if(iter < resolution) {
		iter++;
		Voxel **voxels = v->subdivide();
		for (int i = 0; i < 4; ++i) {
			int n = voxels[i]->intersectsSphere(orig, rayon);
			if(n == 0) {
				voxels[i]->draw();
				delete(voxels[i]);
			} else if (n == 4) {
				delete(voxels[i]);
			} else {
				stepSphere(voxels[i], orig, rayon, resolution, iter);
			}
		}
	}
	delete v;
}

void displaySphereVolumic(Point* orig, double rayon, double resolution) {
	Voxel *v = new Voxel(orig, rayon * 2);
	stepSphere(v, orig, rayon, resolution, 0);
}

int Voxel::intersectsCylindre(Point* orig, Vector* direction, double rayon) {
	int n = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			Vector v(orig->getX() + direction->getX(), orig->getY() + direction->getY(), orig->getZ() + direction->getZ());
			Point* proj = sommets[i][j]->projectOnLine(&v, orig);
			Vector vecProj(proj->getX(), proj->getY(), proj->getZ());
			Vector dist(sommets[i][j], proj);
			// std::cout << "norme : " << proj << std::endl;
			delete proj;
			if(vecProj.getNorme() > direction->getNorme()) {
				n++;
			} else 
			if(dist.getNorme() > rayon) {
				n++;
			}
		}	
	}
	return n;
}

void stepCylindre(Voxel *v, Vector* direction, Point *orig, double rayon, double resolution, double iter) {
	if(iter < resolution) {
		iter++;
		Voxel **voxels = v->subdivide();
		for (int i = 0; i < 8; ++i) {
			int n = voxels[i]->intersectsCylindre(orig, direction, rayon);
			if(n == 0) {
				voxels[i]->draw();
				delete(voxels[i]);
			} else if (n == 8) {
				delete(voxels[i]);
			} else {
				stepCylindre(voxels[i], direction, orig, rayon, resolution, iter);
			}
		}
	}
	// delete v;
}

void displayCylindreVolumic(Point* orig, Vector* direction, double rayon, double resolution) {
	Voxel *v = new Voxel(orig, direction->getNorme() * 3);
	stepCylindre(v, direction, orig, rayon, resolution, 0);
}


#endif