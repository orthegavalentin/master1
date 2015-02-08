#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

void histo(OCTET *in, int lignes, int colonnes) {
	int i;

	int histor[256] = {0};
	int histog[256] = {0};
	int histob[256] = {0};

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		histor[in[i]]++;
		histog[in[i+1]]++;
		histob[in[i+2]]++;	
	}

	for (i=0; i < 256; i++) {
		printf("%d %d %d %d\n", i, histor[i], histog[i], histob[i]);
	}
}

float* densiteProba(OCTET *in, int lignes, int colonnes, int couleur) {
	int i;

	float *proba = malloc(256 * sizeof(int));
	int histo[256] = {0};

	bzero(proba, 256);

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		histo[in[i + couleur]]++;	
	}

	proba[0] = (float) histo[0] / (float) (lignes * colonnes);

	for (i=1; i < 256; i++) {
		proba[i] = proba[i - 1] + (float) histo[i] / (float) (lignes * colonnes);
	}

	return proba;
}

void egalisation(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i;

	float* probar = densiteProba(in, lignes, colonnes, 0);
	float* probag = densiteProba(in, lignes, colonnes, 1);
	float* probab = densiteProba(in, lignes, colonnes, 2);

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i] = probar[in[i]] * 255;
		out[i+1] = probag[in[i+1]] * 255;
		out[i+2] = probab[in[i+2]] * 255;
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

	histo(ImgIn, lignes, colonnes);
	egalisation(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);
	return 1;
}
