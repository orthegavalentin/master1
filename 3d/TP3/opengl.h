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

int n = 0;


void DrawCurve(Point **pts, long nbPts) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nbPts; ++i) {
		glVertex3f(pts[i]->getX(), pts[i]->getY(), pts[i]->getZ());
	}
	glEnd();
}

void drawSurface(Point*** pts, long nbu, long nbv) {
	for (int i = 0; i < nbu-1; ++i) {
		for (int j = 0; j < nbv-1; ++j) {
			glBegin(GL_LINES);
				glVertex3f(pts[i][j]->getX(), pts[i][j]->getY(), pts[i][j]->getZ());
				glVertex3f(pts[i+1][j]->getX(), pts[i+1][j]->getY(), pts[i+1][j]->getZ());
			glEnd();	
			glBegin(GL_LINES);
				glVertex3f(pts[i+1][j]->getX(), pts[i+1][j]->getY(), pts[i+1][j]->getZ());
				glVertex3f(pts[i+1][j+1]->getX(), pts[i+1][j+1]->getY(), pts[i+1][j+1]->getZ());
			glEnd();
		}
	}
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
	n++;
	if(nbPts == 1) {
		return t[0];
	} else {
		Point* pts[nbPts - 1];
		for (int i = 0; i < nbPts - 1; ++i) {
			Vector v(t[i+1], t[i]);
			if(n == 1) {
				glColor3f(1.0, 1.0, 1.00);
				glPointSize(10);
				glBegin(GL_POINTS);
				glVertex3f(t[i]->getX(), t[i]->getY(), t[i]->getZ());
				glVertex3f(t[i+1]->getX(), t[i+1]->getY(), t[i+1]->getZ());
				glEnd();
				glPointSize(1);
			}
			if(n > 6 && n < 18) {
				glColor3f(0.0, 1.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(t[i]->getX(), t[i]->getY(), t[i]->getZ());
				glVertex3f(t[i+1]->getX(), t[i+1]->getY(), t[i+1]->getZ());
				glEnd();
			}
			v.mul(u);
			Point *p = new Point(v.getX() + t[i]->getX(),
				v.getY() + t[i]->getY(),
				v.getZ() + t[i]->getZ());
			pts[i] = p;
		}
		return step(pts, nbPts - 1, u);
	}
}

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

Point **discretiser(std::function<Point*(double)> f, int nbU) {
	Point** pts = new Point*[nbU];
	for (int i = 0; i < nbU; ++i) {
		double u = 1.0/(nbU-1) * (double) i;
		pts[i] = f(u);
	}
	return pts;
}

Point ***surfaceReglee(Point** c1, int nbu, Point** c2, int nbv) {
	Point *** pts = new Point**[nbu];
	for (int i = 0; i < nbu; ++i) {
		pts[i] = new Point*[nbv];
		for (int j = 0; j < nbv; ++j) {
			Point* p = new Point(c1[i]->getX() + c2[j]->getX(),
				c1[i]->getY() + c2[j]->getY(),
				c1[i]->getZ() + c2[j]->getZ());
			pts[i][j] = p;
		}
	}
	return pts;
}


Point ***discretiserDeux(std::function<Point*(double, double)> f, int nbu, int nbv) {
	Point ***pts = new Point**[nbu];
	for (int i = 0; i < nbu; ++i) {
		double u = 1.0/(nbu-1) * (double) i;
		pts[i] = new Point*[nbv];
		for (int j = 0; j < nbv; ++j) {
			double v = 1.0/(nbv-1) * (double) j;
			pts[i][j] = f(u, v);
		}
	}
	return pts;
}

Point* stepDeux(Point **c1, int n1, double u, Point **c2, int n2, double v) {
	if(n1 == 1) {
		return c1[0];
	} else {
		Point* pts[n1 - 1];
		for (int i = 0; i < n1 - 1; ++i) {
			Vector vecu(c1[i+1], c1[i]);
			vecu.mul(u);

			for (int j = 0; j < n2 - 1; ++j) {
				Vector vecv(c2[j+1], c2[j]);
				vecv.mul(v);
				Vector out(vecu.getX() + vecv.getX(),
					vecu.getY() + vecv.getY(),
					vecu.getZ() + vecv.getZ());
				Point *p = new Point(out.getX() + c1[i]->getX(),
					out.getY() + c1[i]->getY(),
					out.getZ() + c1[i]->getZ());
				pts[i] = p;
			}
		}
		return stepDeux(pts, n1 - 1, u, c2, n2, v);
	}
}

std::function<Point*(double, double)> bezierSurfaceByCasteljau(Point** c1, long n1, Point** c2, long n2) {

	auto curbeB = [] (Point** c1, long n1, Point ** c2, long n2) -> std::function<Point*(double, double)>
	{
		return ([=] (double u, double v) {
			return stepDeux(c1, n1, u, c2, n2, v);
			
		});
	};
	auto f = curbeB(c1, n1, c2, n2);
	return f;
}

Point ***surfaceCasteljau(Point** c1, long nb1, long nbu, Point** c2, long nb2, long nbv) {

	for (int i = 0; i < nb1; ++i)
	{
		for (int j = 0; j < nb2; ++j)
		{
			n = 0;
			Point **temp = new Point*[nb1];
			for (int k = 0; k < nb1; ++k)
			{
				temp[k] = new Point(c1[k]->getX() + c2[j]->getX(), 
					c1[k]->getY() + c2[j]->getY(), 
					c1[k]->getZ() + c2[j]->getZ());
			}
			discretiser(bezierCurveByCasteljau(temp, nb1), nbu);
		}
	}

	for (int i = 0; i < nb2; ++i)
	{
		for (int j = 0; j < nb1; ++j)
		{
			n = 0;
			Point **temp = new Point*[nb2];
			for (int k = 0; k < nb2; ++k)
			{
				temp[k] = new Point(c2[k]->getX() + c1[j]->getX(), 
					c2[k]->getY() + c1[j]->getY(), 
					c2[k]->getZ() + c1[j]->getZ());
			}
			discretiser(bezierCurveByCasteljau(temp, nb2), nbv);
		}
	}

	Point **p = discretiser(bezierCurveByCasteljau(c1, nb1), nbu);
	Point **q = discretiser(bezierCurveByCasteljau(c2, nb2), nbv);

	Point*** t = new Point**[nbu];
	for (int i = 0; i < nbu; ++i)
	{
		t[i] = new Point*[nbv];
		for (int j = 0; j < nbv; ++j)
		{
			t[i][j] = new Point(p[i]->getX() + q[j]->getX(), 
				p[i]->getY() + q[j]->getY(), 
				p[i]->getZ() + q[j]->getZ());
		}
	}
	return t;
}


#endif