#include <iostream>
#include "RawReader.h"


int main() {
	RawReader *r = new RawReader("/home/noe/Téléchargements/WHATISIT/whatisit.301x324x56.1.1.1.4.img",
		301, 324, 56);
	std::cout << "min : " << r->getMinValue() << std::endl;
	std::cout << "max : " << r->getMaxValue() << std::endl;

	std::cout << "at 200 200 20 : " << r->getValue(200, 200, 20) << std::endl;
	r->aip("aip.0.raw");
	r->mip("mip.0.raw");
	r->minip("minip.0.raw");
}