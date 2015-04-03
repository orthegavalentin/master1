#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

float avg(OCTET* in, int lignes, int colonnes) {
	unsigned long a = 0;
	int i;
	for (i = 0; i < lignes * colonnes; ++i)
	{
		a += in[i];
	}

	return (double) a / (double) (lignes * colonnes);
}

long main(long argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.pgm";

	int lignes, colonnes, nTaille, S;

	sscanf (argv[1],"%s",cNomImgLue);

	OCTET *ImgIn, *ImgOut, *ImgOut1;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut1, OCTET, nTaille);

	float f = avg(ImgIn, lignes, colonnes);

	printf("%f\n", f);

	free(ImgIn);
	return 1;
}
