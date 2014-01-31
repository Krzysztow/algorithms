#include "division.h"

#include <iostream>


int Division::divide(int nom, int denom) {
	int intParts;
	
	//make them positive numbers
	if (nom < 0)
		nom = -nom;
	if (denom < 0)
		denom = -denom;
	else if (0 == denom) {
		std::wcerr << "Error: zero division";
		return -1;
	}
	
	nom -= denom;
	for (intParts = 0; nom >= 0; ++intParts) {
		nom -= denom;
	}
	
	return intParts;
}
