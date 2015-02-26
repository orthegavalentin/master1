#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"


void flouterFond(OCTET *in, OCTET *out, OCTET *fond, int lignes, int colonnes) {

	int i;
	int strength = 5;

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		if(fond[i/3] == 255) {
			out[i] = getAvgOfNeighbors(in, lignes, colonnes, i, strength);
			out[i+1] = getAvgOfNeighbors(in, lignes, colonnes, i+1, strength);
			out[i+2] = getAvgOfNeighbors(in, lignes, colonnes, i+2, strength);
		} else {
			out[i] = in[i];
			out[i+1] = in[i+1];
			out[i+2] = in[i+2];
		}
	}
}

int getAvgOfNeighbors(OCTET *in, int lignes, int colonnes, int index, int nbN) {
	nbN = (nbN % 2 == 1)?nbN+1:nbN;

	int topLeft = index;
	int i, j, iTemp;
	int sum = 0;

	for (i = 0; i < nbN / 2; ++i) {
		topLeft = coul_indexW(topLeft, lignes, colonnes);	
	}

	for (i = 0; i < nbN / 2; ++i) {
		topLeft = coul_indexN(topLeft, lignes, colonnes);	
	}

	for (i = 0; i < nbN; ++i) {
		iTemp = topLeft;
		for (j = 0; j < nbN; ++j) {
			sum += in[iTemp];
			iTemp = coul_indexE(iTemp, lignes, colonnes);
		}
		topLeft = coul_indexS(topLeft, lignes, colonnes);
	}
	return sum / (nbN * nbN);
}

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char fond[250];
	char out[250] = "out1.ppm";

	int lignes, colonnes, nTaille, S;

	if (argc == 3) {
		sscanf (argv[1],"%s",cNomImgLue);
		sscanf (argv[2],"%s",fond);
	} else {
		printf("to many arguments");
	}


	OCTET *ImgIn, *ImgOut, *ImgFond;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes * 3;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	allocation_tableau(ImgFond, OCTET, lignes * colonnes);
	lire_image_pgm(fond, ImgFond, lignes * colonnes);

	flouterFond(ImgIn, ImgOut, ImgFond, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);

	free(ImgIn);
	return 1;
}
