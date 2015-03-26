#include <iostream>
#include "RawReader.h"


int main() {
	RawReader *r = new RawReader("/home/noe/Téléchargements/MANIX/manixSansIV.512x512x48.0.4570x0.4570x3.0.img",
		512, 512, 48);
	r->marchingCubes(0.4570, 0.4570, 3.0, 1250, "");
}