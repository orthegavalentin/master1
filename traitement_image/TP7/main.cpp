#include <iostream>
#include "RawReader.h"


int main() {
	RawReader *r = new RawReader("/auto_home/nlephilippe/Téléchargements/engine/engine.256x256x128.1x1x1.img",
		256, 256, 128);
	r->marchingCubes(1, 1, 1, 100, "");
}