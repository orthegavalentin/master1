#include <stdio.h>
#include "../lib_c/image_ppm.h"

int main(int argc, char* argv[])
{
	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille, S;

	if (argc != 4) {
		printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%d",&S);

	OCTET *ImgIn, *ImgOut;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);

	int i,j;

	for (i=0; i < nH; i++)
		for (j=0; j < nW; j++) {

			OCTET* pixel = &ImgIn[i*nW+j];

			if (*pixel < S) {
				*pixel = 0;
			} else {
				*pixel = 255;
			}
		}

		ecrire_image_pgm(cNomImgEcrite, ImgIn,  nH, nW);
		free(ImgIn);
		return 1;
	}
