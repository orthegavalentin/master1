#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"


struct region {
	OCTET* data;
	int size;
	struct region *c1;
	struct region *c2;
	struct region *c3;
	struct region *c4;
	int startIndex;
};

void init(OCTET* in, int size, struct region* r, int startIndex) {
	r->size = size;
	r->startIndex = startIndex;

	allocation_tableau(r->data, OCTET, size);
	int i;

	for (i = 0; i < size; ++i) {
		r->data[i] = in[i];
	}

	r->c1 = NULL;
}

void sub_array(OCTET* in, int start, int end, OCTET* out) {
	int i, j, k = 0;
	int size = sqrt(end - start);

	for (i = 0; i < size; ++i) {
		for (j = start+i*size; j < (i + 1) * size + start; ++j) {
			out[k++] = in[j];
		}
	}
}

void split(struct region* r) {
	struct region *c1 = malloc(sizeof(struct region));
	struct region *c2 = malloc(sizeof(struct region));
	struct region *c3 = malloc(sizeof(struct region));
	struct region *c4 = malloc(sizeof(struct region));

	OCTET o[r->size / 4];


	sub_array(r->data, 0, r->size / 4, o);
	init(o, r->size / 4, c1, r->startIndex);

	printf("data : %d\n", r->data[65536]);
	sub_array(r->data, r->size / 4, 2 * (r->size / 4), o);
	init(o, r->size / 4, c2, r->startIndex + r->size / 4);

	sub_array(r->data, 2 * (r->size / 4), 3 * (r->size / 4), o);
	init(o, r->size / 4, c3, r->startIndex + 2 * (r->size / 4));

	sub_array(r->data, 3 * (r->size / 4), r->size, o);
	init(o, r->size / 4, c4, r->startIndex + 3 * (r->size / 4));

	c1->size = r->size / 4;
	c2->size = r->size / 4;
	c3->size = r->size / 4;
	c4->size = r->size / 4;

	r->c1 = c1;
	r->c2 = c2;
	r->c3 = c3;
	r->c4 = c4;

	printf("start of c1 : %d\n", c1->startIndex);
	printf("start of c2 : %d\n", c2->startIndex);
	printf("start of c3 : %d\n", c3->startIndex);
	printf("start of c4 : %d\n", c4->startIndex);

	free(r->data);
}

void merge(struct region* r, OCTET* in) {
	int i;

	if(r->c1 == NULL) {
		printf("merge with start = %d\n", r->startIndex);
		int avg = 0;

		int j, k = 0;
		int size = sqrt(r->size);

		for (i = 0; i < r->size; ++i) {
			avg += r->data[i];
		}

		avg /= r->size;


		for (i = 0; i < size; ++i) {
			for (j = r->startIndex+i*size; j < (i + 1) * size + r->startIndex; ++j) {
				in[j] = avg;
			}
		}
		printf("%d\n", j);
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
	char out[250] = "out.pgm";

	int lignes, colonnes, nTaille, S;

	if (argc == 1) {
		sscanf (out, "%s", cNomImgLue);
	} else if (argc == 2) {
		sscanf (argv[1],"%s",cNomImgLue);
	} else {
		printf("to many arguments");
	}

	OCTET *ImgIn, *ImgOut, *seuil;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	printf("size : %d\n", nTaille);
	struct region root;
	init(ImgIn, lignes * colonnes, &root, 0);
	split(&root);
	merge(&root, ImgOut);

	ecrire_image_pgm(out, ImgOut, lignes, colonnes);

	free(ImgIn);
	return 1;
}
