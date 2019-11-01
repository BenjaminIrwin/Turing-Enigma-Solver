#include <iostream>
#include "enigma.h"
#include "errors.h"
using namespace std;

int main () 
{

	Enigma plugboard;

	plugboard.set_plugboard("test.pb");

	Enigma rotor1;

	rotor1.set_rotor("test.rot");

	rotor1.set_rotor_pos("test.pos", 3);

	Enigma reflector;

	reflector.set_reflector("test.rf");

	return 0;
}
