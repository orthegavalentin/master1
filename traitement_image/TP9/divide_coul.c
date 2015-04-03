#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

long seuil = 20;
long mseuil = 20;

struct region {
	OCTET* data;
	long size;
	struct region *c1;
	struct region *c2;
	struct region *c3;
	struct region *c4;
	struct region *father;
	long startIndex;
	long avgr, avgg, avgb;
	long rec;

};

void init(OCTET* in, long size, struct region* r, long startIndex, struct region* father) {
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
	r->father = father;
}

long esperance(struct region *r) {
	long vr = 0, vg = 0, vb = 0;
	long i, j;
	r->avgr = 0;
	r->avgg = 0;
	r->avgb = 0;

	long side = sqrt(r->size);

	for (i = 0; i < side; ++i) {
		for (j = 0; j < side; ++j) {
			r->avgr += max(r->data[3 * (r->startIndex + i * (2 * side * r->rec) + j)], 0);
			r->avgg += max(r->data[3 * (r->startIndex + i * (2 * side * r->rec) + j)+1], 0);
			r->avgb += max(r->data[3 * (r->startIndex + i * (2 * side * r->rec) + j)+2], 0);
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
	long v = sqrt(vr / r->size) + sqrt(vg / r->size) + sqrt(vb / r->size);
	return v / 3;
}

void sub_array(long index, long size, long *startIndex, long rec) {
	long i, j, l, k = 0;

	long side = sqrt(size);
	switch(index) {
		case 0 : *startIndex = 0; break;
		case 1 : *startIndex = side; break;
		case 2 : *startIndex = 2 * size * rec; break;
		case 3 : *startIndex = 2 * size * rec + side; break;
	}
}

void split(struct region* r) {
	if(r->size > 256) {
		struct region *c1 = malloc(sizeof(struct region));
		struct region *c2 = malloc(sizeof(struct region));
		struct region *c3 = malloc(sizeof(struct region));
		struct region *c4 = malloc(sizeof(struct region));


		long startIndex;
		sub_array(0, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c1, r->startIndex + startIndex, r);
		c1->rec = r->rec * 2;

		sub_array(1, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c2, r->startIndex + startIndex, r);
		c2->rec = r->rec * 2;

		sub_array(2, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c3, r->startIndex + startIndex, r);
		c3->rec = r->rec * 2;

		sub_array(3, r->size / 4, &startIndex, r->rec);
		init(r->data, r->size / 4, c4, r->startIndex + startIndex, r);
		c4->rec = r->rec * 2;

		c1->size = r->size / 4;
		c2->size = r->size / 4;
		c3->size = r->size / 4;
		c4->size = r->size / 4;

		c1->data = r->data; r->c1 = c1; 
		c2->data = r->data; r->c2 = c2;
		c3->data = r->data; r->c3 = c3;
		c4->data = r->data; r->c4 = c4;

		esperance(c1);
			split(c1);
		esperance(c2);
			split(c2);
		esperance(c3);
			split(c3);
		esperance(c4);
			split(c4);
	}
}

void merge(struct region* r, OCTET* in) {
	long i;

	if(r->c1 == NULL) {
		long avg = 0;

		long j, l, k = 0;
		long side = sqrt(r->size);

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

OCTET* reechantilloner (OCTET* tab, int size, int newEch) {
	OCTET* newTab;
	allocation_tableau(newTab, OCTET, newEch * newEch);
	int diff = size / newEch;
	printf("diff : %d\n", diff);
	int i;

	for (i = 0; i < newEch; ++i)
	{
		newTab[i] = 0;
	}

	for (i = 0; i < size * size; ++i)
	{
		newTab[i / (diff * diff)] += tab[i];
	}
	return newTab;
}

// void ceilMerge(struct region* r, int *bool) {
// 	long i;

// 	if(r->c1 == NULL && r->c2 == NULL && r->c3 == NULL && r->c4 == NULL) {
// 		r = r->father;

// 		long avgr = (r->c1->avgr + r->c2->avgr + r->c3->avgr + r->c4->avgr) / 4;
// 		long avgg = (r->c1->avgg + r->c2->avgg + r->c3->avgg + r->c4->avgg) / 4;
// 		long avgb = (r->c1->avgb + r->c2->avgb + r->c3->avgb + r->c4->avgb) / 4;
// 		int v1 = (sqrt(pow(r->c1->avgr - avgr, 2)) + sqrt(pow(r->c2->avgr - avgr, 2)) + sqrt(pow(r->c3->avgr - avgr, 2)) + sqrt(pow(r->c4->avgr - avgr, 2))) / 4;
// 		int v2 = (sqrt(pow(r->c1->avgg - avgg, 2)) + sqrt(pow(r->c2->avgg - avgg, 2)) + sqrt(pow(r->c3->avgg - avgg, 2)) + sqrt(pow(r->c4->avgg - avgb, 2))) / 4;
// 		int v3 = (sqrt(pow(r->c1->avgb - avgb, 2)) + sqrt(pow(r->c2->avgb - avgb, 2)) + sqrt(pow(r->c3->avgb - avgb, 2)) + sqrt(pow(r->c4->avgb - avgb, 2))) / 4;
// 		if((v1 + v2 + v2) / 3 < mseuil) {
// 			*bool = 1;
// 			r->avgr = avgr;
// 			r->avgg = avgg;
// 			r->avgb = avgb;
// 			r->c1 = NULL;
// 			r->c2 = NULL;
// 			r->c3 = NULL;
// 			r->c4 = NULL;
// 		}
// 	} else {
// 		if (r->c1 != NULL) ceilMerge(r->c1, bool);
// 		if (r->c2 != NULL) ceilMerge(r->c2, bool);
// 		if (r->c3 != NULL) ceilMerge(r->c3, bool);
// 		if (r->c4 != NULL) ceilMerge(r->c4, bool);
// 	}
// }

long main(long argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.pgm";
	char out1[250] = "out1.ppm";

	int lignes, colonnes, nTaille, S;

	if (argc == 2) {
		sscanf (out, "%s", cNomImgLue);
		sscanf (argv[2], "%ld", &seuil);
	} else if (argc == 3) {
		sscanf (argv[1],"%s",cNomImgLue);
		sscanf (argv[2], "%ld", &seuil);
	} else {
		printf("to many arguments");
	}

	OCTET *ImgIn, *ImgOut, *ImgOut1;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	// allocation_tableau(ImgOut, OCTET, nTaille);
	// allocation_tableau(ImgOut1, OCTET, nTaille);

	// struct region root;
	// init(ImgIn, lignes * colonnes, &root, 0, NULL);
	// split(&root);
	// merge(&root, ImgOut);
	// // int bool = 1;
	// // int cpt = 0;
	// // 	ceilMerge(&root, &bool);

	// merge(&root, ImgOut1);

	ecrire_image_pgm(out, reechantilloner(ImgIn, 512, 16), 16, 16);
	// ecrire_image_ppm(out1, ImgOut1, lignes, colonnes);

	free(ImgIn);
	return 1;
}
