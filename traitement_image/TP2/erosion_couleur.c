#include <stdio.h>

#include "utils.h"
#include "../lib_c/image_ppm.h"
#include "math.h"

void eroder(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i, j;

	for (i=0; i < lignes * colonnes * 3; i++) {
		for (j = 0; j < 3; ++j)
		{
			int index = i + j;

			int val = in[index];
			int n = in[coul_indexN(index, colonnes)];
			int s = in[coul_indexS(index, lignes, colonnes)];
			int e = in[coul_indexE(index, lignes, colonnes)];
			int w = in[coul_indexW(index)];

			int m = max(n, s);
			m = max(m, e);
			m = max(m, w);

			out[index] = m;		
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

	eroder(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);

	return 1;
}
