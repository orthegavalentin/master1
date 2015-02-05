#include <stdio.h>

#include "utils.h"
#include "../lib_c/image_ppm.h"
#include "math.h"

#define seuil 90

void dilater(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int index;

	for (index=0; index < lignes * colonnes; index++) {
		int val = in[index];
		int n = in[indexN(index, colonnes)];
		int s = in[indexS(index, lignes, colonnes)];
		int e = in[indexE(index, lignes, colonnes)];
		int w = in[indexW(index)];

		int m = min(n, s);
		m = min(m, e);
		m = min(m, w);

		out[index] = m;				
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

	dilater(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_pgm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);

	return 1;
}
