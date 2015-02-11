#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

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

float* densiteProbaInv(float* toInv) {
	int i;

	float *proba = malloc(256 * sizeof(int));
	bzero(proba, 256);

	proba[0] = toInv[255] - toInv[254];

	for (i=1; i < 256; i++) {
		//printf("toInv[%d] : %f\n", i, toInv[i]);
		proba[i] = toInv[255 - i] - toInv[255 - i - 1] + proba[i - 1];
		//printf("%d %f %f\n", i, toInv[i], proba[i]);
	}

	return proba;
}

void egalisation(OCTET *in, OCTET *out, int lignes, int colonnes, float *probar, float *probag, float *probab) {

	int i;

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i] = probar[in[i]] * 255;
		out[i+1] = probag[in[i+1]] * 255;
		out[i+2] = probab[in[i+2]] * 255;
	}
}

void egalisationInv(OCTET *in, OCTET *out, int lignes, int colonnes, float *probar, float *probag, float *probab) {

	int i;

	float* invr = densiteProbaInv(probar);
	float* invg = densiteProbaInv(probag);
	float* invb = densiteProbaInv(probab);

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i] = invr[in[i]] * 255;
		out[i+1] = invg[in[i+1]] * 255;
		out[i+2] = invb[in[i+2]] * 255;
	}
}

int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char cNomImgLue2[250];
	char out[250] = "out.ppm";
	char out2[250] = "out2.ppm";


	int lignes, colonnes, nTaille, S;
	int lignes2, colonnes2, nTaille2;

	if (argc == 2) {
		sscanf (out, "%s", cNomImgLue);
	} else if (argc == 3) {
		sscanf (argv[1],"%s",cNomImgLue);
		sscanf (argv[2],"%s",cNomImgLue2);			
	} else {
		printf("to many arguments");
	}


	OCTET *ImgIn, *ImgOut, *ImgIn2, *ImgOut2;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes * 3;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue2, &lignes2, &colonnes2);
	nTaille2 = lignes2 * colonnes2 * 3;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	allocation_tableau(ImgIn2, OCTET, nTaille2);
	lire_image_ppm(cNomImgLue2, ImgIn2, lignes2 * colonnes2);
	allocation_tableau(ImgOut2, OCTET, nTaille2);


	float* probar = densiteProba(ImgIn, lignes, colonnes, 0);
	float* probag = densiteProba(ImgIn, lignes, colonnes, 1);
	float* probab = densiteProba(ImgIn, lignes, colonnes, 2);

	egalisation(ImgIn, ImgOut, lignes, colonnes, probar, probag, probab);

	float* probar2 = densiteProba(ImgIn2, lignes2, colonnes2, 0);
	float* probag2 = densiteProba(ImgIn2, lignes2, colonnes2, 1);
	float* probab2 = densiteProba(ImgIn2, lignes2, colonnes2, 2);

	egalisation(ImgIn2, ImgOut2, lignes2, colonnes2, probar2, probag2, probab2);
	egalisationInv(ImgOut2, ImgIn2, lignes2, colonnes2, probar, probag, probab);

	ecrire_image_ppm(out2, ImgIn2,  lignes2, colonnes2);
	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);
	return 1;
}
