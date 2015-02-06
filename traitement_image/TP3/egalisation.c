#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

void histo(OCTET *in, int lignes, int colonnes) {
	int i;
	int histo[256] = {0};

	for (i=0; i < lignes * colonnes; i++) {
		histo[in[i]]++;	
	}

	for (i = 0; i < 255; ++i)
	{
		printf("%d %d\n", i, histo[i]);
	}
}

int* densiteProba(OCTET *in, int lignes, int colonnes, int a, int b) {
	int i;

	int *proba = malloc(256 * sizeof(int));

	for (i=0; i < lignes * colonnes; i++) {
		histo[in[i]]++;	
	}
}

void egalisation(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i;

	int a = 255, b = 0;

	int histo[256] = {0};

	for (i=0; i < lignes * colonnes; i++) {

		a = min(a, in[i]);
		b = max(b, in[i]);
		histo[in[i]]++;	
	}

	float delta = 255.0 / (b - a);


	for (i=0; i < lignes * colonnes; i++) {
		out[i] = (in[i] - a) * 255 / (b - a);
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


	OCTET *ImgIn, *ImgOut, *ImgOut1;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);


	histo(ImgIn, lignes, colonnes);
	egalisation(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_pgm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);

	return 1;
}
