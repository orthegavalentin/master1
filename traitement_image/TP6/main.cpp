#include <iostream>
#include "RawReader.h"


int main() {
	RawReader *r = new RawReader("/auto_home/nlephilippe/Téléchargements/BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img",
		256, 256, 100);
	std::cout << "min : " << r->getMinValue() << std::endl;
	std::cout << "max : " << r->getMaxValue() << std::endl;

	std::cout << "at 200 200 20 : " << r->getValue(200, 200, 20) << std::endl;
	
}