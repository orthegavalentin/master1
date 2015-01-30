#include <stdio.h>
#include "../lib_c/image_ppm.h"

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	int type, val;
	int nH, nW, nTaille;

	if (argc != 4) {
		printf("Usage: ImageIn.pgm ligne (0-1) val \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%d",&type);
	sscanf (argv[3],"%d",&val);

	OCTET *ImgIn;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	
	int i;

	if(type == 0) {
		for (i = 0; i < nH; ++i) {
			printf("%d %d\n", i, ImgIn[i*nW+val]);
		}
	} else {
		for (i = 0; i < nW; ++i) {
			printf("%d %d\n", i, ImgIn[val*nH + i]);
		}
	}

	free(ImgIn);
	return 1;
}
