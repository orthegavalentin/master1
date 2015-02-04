#include <stdio.h>

#include "../lib_c/image_ppm.h"
#include "math.h"

void difference (OCTET *seuil, OCTET *dilatee, OCTET *out, int size) {
  int i;
  for(i = 0; i < size; i++) {
    if (seuil[i] != dilatee[i]) {
      out[i] = 0;
    } else {
      out[i] = 255;
    }
  }
}

int main(int argc, char* argv[])
{
  char seuil[250];
  char dilatee[250];
    
  char out[250] = "out.pgm";
       
  int lignes, colonnes, nTaille, S;


  if (argc == 3) {
    sscanf (argv[1],"%s", seuil);
    sscanf (argv[2], "%s", dilatee);
  } else {
    printf("to few arguments");
  }


  OCTET *ImgSeuil, *ImgOut, *ImgDil;

  lire_nb_lignes_colonnes_image_pgm(seuil, &lignes, &colonnes);
  nTaille = lignes * colonnes;

  allocation_tableau(ImgSeuil, OCTET, nTaille);
  lire_image_pgm(seuil, ImgSeuil, lignes * colonnes);

  allocation_tableau(ImgDil, OCTET, nTaille);
  lire_image_pgm(dilatee, ImgDil, lignes * colonnes);
  
  allocation_tableau(ImgOut, OCTET, nTaille);

  difference(ImgSeuil, ImgDil, ImgOut, nTaille);

  ecrire_image_pgm(out, ImgOut,  lignes, colonnes);

  return 1;
}
