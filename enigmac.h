#ifndef ENIGMAC_H 
#define ENIGMAC_H

#include <iostream>
#include <fstream>
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

class Enigma
{
public:
	bool set_enigma(int argc, char** argv, int& error);

	bool encrypt(std::istream& input, std::ostream& output, int& error);

private:
	Rotor* rotors;
	int num_rotors;
	Plugboard plugboard;
	Reflector reflector; 
};


#endif
