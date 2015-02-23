#ifndef OGL_H
#define OGLH

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <functional>

#include "point.h"
#include "vector.h"

#include <iostream>
#include <GL/glut.h>


void DrawCurve(Point **pts, long nbPts) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nbPts; ++i) {
		glVertex3f(pts[i]->getX(), pts[i]->getY(), pts[i]->getZ());
	}
	glEnd();
}

Point **HermiteCubicCurve(Point *p0, Point *p1, Vector *v0, Vector *v1, long nbU) {

	Point **pts = new Point*[nbU];

	for (int i = 0; i < nbU; ++i)
	{
		float u = 1 / (float) nbU * (float) i;

		double f1 = 2 * pow(u, 3) - 3 * pow(u, 2) + 1;
		double f2 = -2 * pow(u, 3) + 3 * pow(u, 2);
		double f3 = pow(u, 3) - 2 * pow(u, 2) + u;
		double f4 = pow(u, 3) - pow(u, 2);

		pts[i] = new Point(f1 * p0->getX() + f2 * p1->getX() + f3 * v0->getX() + f4 * v1->getX(),
			f1 * p0->getY() + f2 * p1->getY() + f3 * v0->getY() + f4 * v1->getY(),
			f1 * p0->getZ() + f2 * p1->getZ() + f3 * v0->getZ() + f4 * v1->getZ());
	}
	return pts;
}


long facto(long n) {
	if(n == 0) {
		return 1;
	}
	return n * facto(n - 1);
}

Point* step(Point **t, int nbPts, double u) {
	if(nbPts == 1) {
		return new Point(t[0]->getX(), t[0]->getY(), t[0]->getZ());
	} else {
		Point* pts[nbPts - 1];
		for (int i = 0; i < nbPts - 1; ++i) {
			Vector v(t[i+1], t[i]);
			glColor3f(0.0, 1.0, 1.0);
			glBegin(GL_LINES);
				glVertex3f(t[i]->getX(), t[i]->getY(), t[i]->getZ());
				glVertex3f(t[i+1]->getX(), t[i+1]->getY(), t[i+1]->getZ());
			glEnd();
			v.mul(u);
			Point *p = new Point(v.getX() + t[i]->getX(),
				v.getY() + t[i]->getY(),
				v.getZ() + t[i]->getZ());
			pts[i] = p;
		}
		return step(pts, nbPts - 1, u);
	}
}

/*Point **BezierCurveByCasteljau(Point **t, long nbPts, long nbU) {
	Point **pts = new Point*[nbU];

	for (int j = 0; j < nbU; ++j)
	{
		float u = (1.0f / (float) (nbU - 1))* (float) j;
		pts[j] = step(t, nbPts, u);
	}

	return pts;
}
*/
std::function<Point*(double)> bezierCurveByBernstein(Point** tab, long nControl) {

	auto curbeB = [] (Point** tab, long nControl) -> std::function<Point*(double)>
	{ return ([=] (double u) {

		double n = nControl-1;

		Point* p = new Point();
		for (int i = 0; i <= n; ++i) {
			double Bni = (facto(n) / (facto(i) * facto(n-i))) * pow(u, i) * pow(1-u, n-i);
			p->setX(p->getX() + Bni*tab[i]->getX());
			p->setY(p->getY() + Bni*tab[i]->getY());
			p->setZ(p->getZ() + Bni*tab[i]->getZ());
		}
		return p;


	}); };
	auto f = curbeB(tab, nControl);
	return f;
}

std::function<Point*(double)> bezierCurveByCasteljau(Point** tab, long nControl) {

	auto curbeB = [] (Point** pts, long nControl) -> std::function<Point*(double)>
	{
		return ([=] (double u) {
			return step(pts, nControl, u);
		});
	};
	auto f = curbeB(tab, nControl);
	return f;
}

Point** discretiser(std::function<Point*(double)> f, int nbU) {
	Point** pts = new Point*[nbU];
	for (int i = 0; i < nbU; ++i) {
		double u = 1.0/(nbU-1) * (double) i;
		pts[i] = f(u);
	}
	return pts;
}

#endif