#include <iostream>
#include "RawReader.h"


int main() {
	RawReader *r = new RawReader("/auto_home/nlephilippe/Téléchargements/WHATISIT/whatisit.301x324x56.1.1.1.4.img",
		301, 324, 56);
	std::cout << "min : " << r->getMinValue() << std::endl;
	std::cout << "max : " << r->getMaxValue() << std::endl;

	std::cout << "at 200 200 20 : " << r->getValue(200, 200, 20) << std::endl;
	r->ex("out.0.raw");
}