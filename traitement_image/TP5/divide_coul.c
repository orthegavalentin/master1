#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

int seuil = 50;

struct region {
	OCTET* data;
	int size;
	struct region *c1;
	struct region *c2;
	struct region *c3;
	struct region *c4;
	int startIndex;
	int avgr, avgg, avgb;
	int rec;
};

void init(OCTET* in, int size, struct region* r, int startIndex) {
	r->size = size;
	r->startIndex = startIndex;

	r->data = in;

	r->c1 = NULL;
	r->c2 = NULL;
	r->c3 = NULL;
	r->c4 = NULL;
	r->rec = 1;

	r->avgr = 0;
	r->avgg = 0;
	r->avgb = 0;
}

int esperance(struct region *r) {
	int vr = 0, vg = 0, vb = 0;
	int i, j;

	int side = sqrt(r->size);

	for (i = 0; i < side; ++i) {
		for (j = 0; j < side; ++j) {
			r->avgr += r->data[3 * (r->startIndex + i * (2 * side * r->rec) + j)];
			r->avgg += r->data[3 * (r->startIndex + i * (2 * side * r->rec) + j)+1];
			r->avgb += r->data[3 * (r->startIndex + i * (2 * side * r->rec) + j)+2];
		}
	}
	r->avgr /= r->size;
	r->avgg /= r->size;
	r->avgb /= r->size;

	for (i = 0; i < side; ++i) {
		for (j = 0; j < side; ++j) {
			vr += pow(r->data[(r->startIndex + i * (2 * side * r->rec) + j) * 3] - r->avgr, 2);
			vg += pow(r->data[(r->startIndex + i * (2 * side * r->rec) + j) * 3] - r->avgg, 2);
			vb += pow(r->data[(r->startIndex + i * (2 * side * r->rec) + j) * 3] - r->avgb, 2);
		}
	}
	int v = sqrt(vr / r->size) + sqrt(vg / r->size) + sqrt(vb / r->size);
	return v / 3;
}

void sub_array(int index, int size, int *startIndex, int rec) {
	int i, j, l, k = 0;

	int side = sqrt(size);
	switch(index) {
		case 0 : *startIndex = 0; break;
		case 1 : *startIndex = side; break;
		case 2 : *startIndex = 2 * size * rec; break;
		case 3 : *startIndex = 2 * size * rec + side; break;
	}
}

void split(struct region* r) {
	if(r->size > 4) {
		struct region *c1 = malloc(sizeof(struct region));
		struct region *c2 = malloc(sizeof(struct region));
		struct region *c3 = malloc(sizeof(struct region));
		struct region *c4 = malloc(sizeof(struct region));


		int startIndex;
		sub_array(0, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c1, r->startIndex + startIndex);
		c1->rec = r->rec * 2;

		sub_array(1, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c2, r->startIndex + startIndex);
		c2->rec = r->rec * 2;

		sub_array(2, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c3, r->startIndex + startIndex);
		c3->rec = r->rec * 2;

		sub_array(3, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c4, r->startIndex + startIndex);
		c4->rec = r->rec * 2;

		c1->size = r->size / 4;
		c2->size = r->size / 4;
		c3->size = r->size / 4;
		c4->size = r->size / 4;

		c1->data = r->data; r->c1 = c1; 
		c2->data = r->data; r->c2 = c2;
		c3->data = r->data; r->c3 = c3;
		c4->data = r->data; r->c4 = c4;

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

void merge(struct region* r, OCTET* in) {
	int i;

	if(r->c1 == NULL) {
		int avg = 0;

		int j, l, k = 0;
		int side = sqrt(r->size);

		for (i = 0; i < side; ++i) {
			for (j = 0; j < side; ++j) {
				l = 3 * (r->startIndex + i * 2 * side * (r->rec / 2) + j);
				in[l] = r->avgr;
				in[l+1] = r->avgg;
				in[l+2] = r->avgb;
			}
		}
	} else {
		merge(r->c1, in);
		merge(r->c2, in);
		merge(r->c3, in);
		merge(r->c4, in);
	}
}

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.ppm";

	int lignes, colonnes, nTaille, S;

	if (argc == 2) {
		sscanf (out, "%s", cNomImgLue);
		sscanf (argv[2], "%d", &seuil);
	} else if (argc == 3) {
		sscanf (argv[1],"%s",cNomImgLue);
		sscanf (argv[2], "%d", &seuil);
	} else {
		printf("to many arguments");
	}

	OCTET *ImgIn, *ImgOut;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes * 3;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	struct region root;
	init(ImgIn, lignes * colonnes, &root, 0);
	split(&root);
	merge(&root, ImgOut);

	ecrire_image_ppm(out, ImgOut, lignes, colonnes);

	free(ImgIn);
	return 1;
}
