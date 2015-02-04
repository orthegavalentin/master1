#include <stdio.h>

#include "utils.h"
#include "../lib_c/image_ppm.h"
#include "math.h"

#define seuil 90

void dilater(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i, j;
	
	for (i=0; i < lignes * colonnes * 3; i++) {
		out[i] = 255;
	}

	for (i=0; i < lignes * colonnes * 3; i++) {
		if(in[i] < seuil) {
			out[coul_indexN(i, colonnes)] = 0;
			out[coul_indexS(i, lignes, colonnes)] = 0;
			out[coul_indexE(i, lignes, colonnes)] = 0;
			out[coul_indexW(i)] = 0;
		}
	}
}


int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.ppm";
	
	int lignes, colonnes, nTaille, S;

	if (argc == 1) {
		sscanf (out, "%s", cNomImgLue);
	} else if (argc == 2) {
		sscanf (argv[1],"%s",cNomImgLue);
	} else {
		printf("to many arguments");
	}


	OCTET *ImgIn, *ImgOut, *ImgOut1;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes * 3;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	dilater(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);

	return 1;
}
