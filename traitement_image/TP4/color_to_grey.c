#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"


void colorToGrey(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i;

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i / 3] = (in[i] + in[i+1] + in[i+2]) / 3;
	}
}

void seuillage(OCTET *in, OCTET *out, int lignes, int colonnes, int seuil) {
	int i;

	for (i=0; i < lignes * colonnes; i++) {
		out[i] = (in[i] > seuil)?255:0;
	}
}

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.pgm";
	char out1[250] = "seuil.pgm";

	int lignes, colonnes, nTaille, S;

	if (argc == 1) {
		sscanf (out, "%s", cNomImgLue);
	} else if (argc == 2) {
		sscanf (argv[1],"%s",cNomImgLue);
	} else {
		printf("to many arguments");
	}


	OCTET *ImgIn, *ImgOut, *seuil;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes * 3;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, lignes * colonnes);
	allocation_tableau(seuil, OCTET, lignes * colonnes);

	colorToGrey(ImgIn, ImgOut, lignes, colonnes);
	histo(ImgOut, lignes, colonnes);
	seuillage(ImgOut, seuil, lignes, colonnes, 185);

	ecrire_image_pgm(out, ImgOut,  lignes, colonnes);
	ecrire_image_pgm(out1, seuil,  lignes, colonnes);

	free(ImgIn);
	return 1;
}
