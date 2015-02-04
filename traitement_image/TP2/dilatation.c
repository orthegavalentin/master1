#include <stdio.h>

#include "utils.h"
#include "../lib_c/image_ppm.h"
#include "math.h"

void dilater(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i, j;
	
	for (i=0; i < lignes; i++) {
		for (j=0; j < colonnes; j++) {
			
			int index = i*colonnes+j;

			int n = in[indexN(index, colonnes)];
			int s = in[indexS(index, lignes, colonnes)];
			int e = in[indexE(index, lignes, colonnes)];
			int w = in[indexW(index)];

			if(n + s + e + w == 255 * 4) {
				out[index] = 255;
			} else {
				out[index] = 0;
			}

			/*out[indexN(index, colonnes)] = in[index];
			out[indexS(index, lignes, colonnes)] = in[index];
			out[indexE(index, lignes, colonnes)] = in[index];
			out[indexW(index)] = in[index];*/

		}
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
