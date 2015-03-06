#include <stdio.h>

// #include "../lib_c/image_ppm.h"
#include "math.h"
// #include "../lib_c/utils.h"

int seuil = 50;

class region {
public:
	ImageBase *img;
	int lignes;
	int colonnes;
	int x;
	int y;
	struct region *c1;
	struct region *c2;
	struct region *c3;
	struct region *c4;
	int avgr, avgg, avgb;

	region(ImageBase *in, int lignes, int colonnes, int x, int y) {
		this->img = in;
		this->lignes = lignes;
		this->colonnes = colonnes;
		this->x = x;
		this->y = y;
		this->c1 = NULL;
		this->c2 = NULL;
		this->c3 = NULL;
		this->c4 = NULL;
		this->avgr = 0;
		this->avgg = 0;
		this->avgb = 0;
	}
};

int esperance(region *r) {
	int vr = 0, vg = 0, vb = 0;
	ImageBase *img = r->img;
	int i, j;
	int index;
	int size = r->lignes * r->colonnes;
	ImageBase* red = img->getPlan(ImageBase::PLAN_R);

	int cpt = 0;

	for (i = 0; i < r->lignes; i += 3) {
		for (j = 0; j < r->colonnes; j += 3) {
			r->avgr += (int)*red[i][j];
			r->avgg += (int)*red[i+1][j+1];
			r->avgb += (int)*red[i+2][j+2];
		}
	}
	printf("r avg : %d\n", r->avgr);
	r->avgr /= size;
	r->avgg /= size;
	r->avgb /= size;

	for (i = 0; i < r->lignes / 3; ++i) {
		for (j = 0; j < r->colonnes / 3; ++j) {
			// vr += pow(r->red[i][j] - r->avgr, 2);
			// vg += pow(r->green[i][j] - r->avgg, 2);
			// vb += pow(r->blue[i][j] - r->avgb, 2);
		}
	}

	int v = sqrt(vr / size) + sqrt(vg / size) + sqrt(vb / size);
	return v / 3;
}

void split(struct region* r) {
	if(r->lignes * r->colonnes > 4) {

		region *c1 = new region(r->img, r->lignes / 2, r->colonnes / 2, r->lignes + r->x, r->colonnes + r->y);
		region *c2 = new region(r->img, r->lignes / 2, r->colonnes / 2, r->lignes * 1.5 + r->x, r->colonnes + r->y);
		region *c3 = new region(r->img, r->lignes / 2, r->colonnes / 2, r->lignes + r->x, r->colonnes * 1.5 + r->y);
		region *c4 = new region(r->img, r->lignes / 2, r->colonnes / 2, r->lignes * 1.5 + r->x, r->colonnes * 1.5 + r->y);

		printf("init in split ok\n");
		if(esperance(c1) > seuil) {
			split(c1);
		}
		if(esperance(c2) > seuil) {
			split(c2);
		}
		if(esperance(c3) > seuil) {
			split(c3);
		}
		if(esperance(c4) > seuil) {
			split(c4);
		}
	}
}

void merge(region* r, ImageBase* in) {
	int i, j;
	int cpt = 0;

	if(r->c1 == NULL) {
		int avg = 0;

		for (i = 0; i < r->lignes; ++i) {
			for (j = 0; j < r->colonnes; ++j) {
				if(cpt % 3 == 0) {
					in->set(r->avgr, i, j);
				} else if(cpt % 3 == 1) {
					in->set(r->avgg, i, j);
				} else if(cpt % 3 == 2) {
					in->set(r->avgb, i, j);
				}
				cpt++;
			}
		}
	} else {
		merge(r->c1, in);
		merge(r->c2, in);
		merge(r->c3, in);
		merge(r->c4, in);
	}
}