#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

int* getSeuils(OCTET *in, int lignes, int colonnes, int couleur) {
	int histo[256] = {0};
	int i, sum = 0;

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		histo[in[i+couleur]]++;
	}

	int smin, smax;

	for (i = 0; i < 256; ++i)
	{
		sum += histo[i];
		if(sum > (float) (colonnes * lignes) * 0.01F) {
			smin = i;
			break;
		}
	}

	sum = 0;

	for (i = 0; i < 256; ++i)
	{
		sum += histo[i];
		if(sum > (float) (colonnes * lignes) * 0.99F) {
			smax = i;
			break;
		}
	}

	int *s = malloc(2 * sizeof(int));
	s[0] = smin;
	s[1] = smax;
	return s;
}


void seuillage(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int *sr = getSeuils(in, lignes, colonnes, 0);
	int *sg = getSeuils(in, lignes, colonnes, 1);
	int *sb = getSeuils(in, lignes, colonnes, 2);

	int i;

	int ar = 255, br = 0;
	int ag = 255, bg = 0;
	int ab = 255, bb = 0;

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		in[i] = min(sr[1], in[i]);
		in[i] = max(sr[0], in[i]);

		in[i+1] = min(sg[1], in[i+1]);
		in[i+1] = max(sg[0], in[i+1]);

		in[i+2] = min(sb[1], in[i+2]);
		in[i+2] = max(sb[0], in[i+2]);
	}

	histo(in, lignes, colonnes);

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		ar = min(ar, in[i]);
		br = max(br, in[i]);

		ag = min(ag, in[i+1]);
		bg = max(bg, in[i+1]);

		ab = min(ab, in[i+2]);
		bb = max(bb, in[i+2]);
	}

	/*printf("rmin : %d\nrmax : %d\n", ar, br);
	printf("gmin : %d\ngmax : %d\n", ag, bg);
	printf("bmin : %d\nbmax : %d\n", ab, bb);*/

	for (i=0; i < 255; i++) {
		//printf("%d %d %d %d\n", i, histor[i], histob[i], histog[i]);
	}

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i] = (in[i] - ar) * 255 / (br - ar);
		out[i+1] = (in[i+1] - ag) * 255 / (bg - ag);
		out[i+2] = (in[i+2] - ab) * 255 / (bb - ab);
	}

	printf("seuils red : %d - %d\n", sr[0], sr[1]);
	printf("seuils green : %d - %d\n", sg[0], sg[1]);
	printf("seuils blue : %d - %d\n", sb[0], sb[1]);
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

	seuillage(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);

	return 1;
}
