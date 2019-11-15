#include <iostream>
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "errors.h"
#include "helper.h"
#include "enigma.h"
using namespace std;

int main (int argc, char* argv[])
{

	int error = 0;
	Enigma enigma;
	
	if(!enigma.set_enigma(argc, argv, error))
		return error;

	if(!enigma.encrypt(cin, cout, error))
		return error;

	return error;
}
