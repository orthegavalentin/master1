#include <stdio.h>
#include "../lib_c/image_ppm.h"
#include "math.h"


void eroder(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i, j;

	for (i=0; i < lignes; i++) {
		for (j=0; j < colonnes; j++) {
			
			int index = i*colonnes+j;

			int n = in[indexN(index, colonnes)];
			int s = in[indexS(index, lignes, colonnes)];
			int e = in[indexE(index, lignes, colonnes)];
			int w = in[indexW(index)];

			if(n + s + e + w == 0) {
				out[index] = 0;
			} else {
				out[index] = 255;
			}

		}
	}
}

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

		}
	}
}

void ouverture(OCTET *in, OCTET *out, int lignes, int colonnes) {
	OCTET* temp;
	allocation_tableau(temp, OCTET, lignes*colonnes);
	eroder(in, temp, lignes, colonnes);
	dilater(temp, out, lignes, colonnes);
	free(temp);
}

void fermeture(OCTET *in, OCTET *out, int lignes, int colonnes) {
	OCTET* temp;
	allocation_tableau(temp, OCTET, lignes*colonnes);
	dilater(in, temp, lignes, colonnes);
	eroder(temp, out, lignes, colonnes);
	free(temp);
}


int indexN(int index, int colonnes) {
	int n = index - colonnes;
	if(n < 0) {
		return 0;
	}
	return n;
}

int indexS(int index, int lignes, int colonnes) {
	int n = index + colonnes;
	if(n > lignes * colonnes) {
		return lignes * colonnes - 1;
	}
	return n;
}

int indexE(int index, int lignes, int colonnes) {
	int n = index + 1;
	if(n > lignes * colonnes) {
		return lignes * colonnes - 1;
	}
	return n;
}

int indexW(int index) {
	int n = index - 1;
	if(n < 0) {
		return 0;
	}
	return n;
}

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char ouv[250] = "ouverture.pgm";
	char fer[250] = "fermeture.pgm";

	int lignes, colonnes, nTaille, S;

	if (argc != 2) {
		printf("Usage: ImageIn.pgm\n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue);

	OCTET *ImgIn, *ImgOut, *ImgOut1;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut1, OCTET, nTaille);

	ouverture(ImgIn, ImgOut, lignes, colonnes);
	fermeture(ImgIn, ImgOut1, lignes, colonnes);

	ecrire_image_pgm(ouv, ImgOut,  lignes, colonnes);
	ecrire_image_pgm(fer, ImgOut1,  lignes, colonnes);
	free(ImgIn);
	return 1;
}
