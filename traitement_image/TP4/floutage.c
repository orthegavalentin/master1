#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"


void flouter(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i;

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i] = (in[coul_indexN(i, lignes, colonnes)] + in[coul_indexS(i, lignes, colonnes)] + in[coul_indexE(i, lignes, colonnes)] + 
				 in[coul_indexW(i, lignes, colonnes)] + in[coul_indexNW(i, lignes, colonnes)] + in[coul_indexNE(i, lignes, colonnes)] + 
				 in[coul_indexSW(i, lignes, colonnes)] + in[coul_indexSE(i, lignes, colonnes)] + in[i]) / 9;

		out[i+1] = (in[coul_indexN(i+1, lignes, colonnes)] + in[coul_indexS(i+1, lignes, colonnes)] + in[coul_indexE(i+1, lignes, colonnes)] + 
				 in[coul_indexW(i+1, lignes, colonnes)] + in[coul_indexNW(i+1, lignes, colonnes)] + in[coul_indexNE(i+1, lignes, colonnes)] + 
				 in[coul_indexSW(i+1, lignes, colonnes)] + in[coul_indexSE(i+1, lignes, colonnes)] + in[i+1]) / 9;

		out[i+2] = (in[coul_indexN(i+2, lignes, colonnes)] + in[coul_indexS(i+1, lignes, colonnes)] + in[coul_indexE(i+2, lignes, colonnes)] + 
				 in[coul_indexW(i+2, lignes, colonnes)] + in[coul_indexNW(i+2, lignes, colonnes)] + in[coul_indexNE(i+2, lignes, colonnes)] + 
				 in[coul_indexSW(i+2, lignes, colonnes)] + in[coul_indexSE(i+2, lignes, colonnes)] + in[i+2]) / 9;


	}
}

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.ppm";
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
	allocation_tableau(ImgOut, OCTET, nTaille);

	flouter(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);

	free(ImgIn);
	return 1;
}
