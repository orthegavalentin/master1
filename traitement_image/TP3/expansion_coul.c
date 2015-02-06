#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

void expansion(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int i;

	int ar = 255, br = 0;
	int ag = 255, bg = 0;
	int ab = 255, bb = 0;

	int histor[256] = {0};
	int histog[256] = {0};
	int histob[256] = {0};

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		ar = min(ar, in[i]);
		br = max(br, in[i]);

		ag = min(ag, in[i+1]);
		bg = max(bg, in[i+1]);

		ab = min(ab, in[i+2]);
		bb = max(bb, in[i+2]);

		histor[in[i]]++;
		histog[in[i+1]]++;
		histob[in[i+2]]++;	
	}

	/*printf("rmin : %d\nrmax : %d\n", ar, br);
	printf("gmin : %d\ngmax : %d\n", ag, bg);
	printf("bmin : %d\nbmax : %d\n", ab, bb);*/

	for (i=0; i < 256; i++) {
		printf("%d %d %d %d\n", i, histor[i], histog[i], histob[i]);
	}

	for (i=0; i < lignes * colonnes * 3; i += 3) {
		out[i] = (in[i] - ar) * 255 / (br - ar);
		out[i+1] = (in[i+1] - ag) * 255 / (bg - ag);
		out[i+2] = (in[i+2] - ab) * 255 / (bb - ab);
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

	expansion(ImgIn, ImgOut, lignes, colonnes);

	ecrire_image_ppm(out, ImgOut,  lignes, colonnes);
	free(ImgIn);

	return 1;
}
