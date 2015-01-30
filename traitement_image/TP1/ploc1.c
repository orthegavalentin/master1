#include <stdio.h>
#include "../lib_c/image_ppm.h"

int* reechantilloner (int* tab, int size, int newEch) {
	int* newTab = malloc(newEch * sizeof(int));


	int diff = size / newEch;
	int i;

	for (i = 0; i < newEch; ++i)
	{
		newTab[i] = 0;
	}

	for (i = 0; i < size; ++i)
	{
		newTab[i / diff] += tab[i];
	}
	return newTab;
}


int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	int type, val;
	int nH, nW, nTaille;

	sscanf (argv[1],"%s",cNomImgLue) ;

	OCTET *ImgIn;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW * 3;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

	int* r = malloc(256 * sizeof(int));
	int* g = malloc(256 * sizeof(int));
	int* b = malloc(256 * sizeof(int));

	int i, j;

	for (i = 0; i < 256; ++i)
	{
		r[i] = 0;
		g[i] = 0;
		b[i] = 0;
	}

	int n = 0;
	for (i=0; i < nH; i++) {
		for (j=0; j < nW; j++) {
			r[ImgIn[i*nW*3 + j*3]]++;
			g[ImgIn[i*nW*3 + j*3 + 1]]++;
			b[ImgIn[i*nW*3 + j*3 + 2]]++;
		}
	}
	
	int ech = 32;

	int* r1 = reechantilloner(r, 256, ech);
	int* g1 = reechantilloner(g, 256, ech);
	int* b1 = reechantilloner(b, 256, ech);
	for (i = 0; i < ech; ++i)
	{
		printf("%d %d %d %d\n", i, r1[i], g1[i], b1[i]);
	}

	free(ImgIn);
	return 1;
}
