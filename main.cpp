#include <iostream>
#include "enigma.h"
#include "errors.h"
using namespace std;

int main () 
{

	Enigma plugboard;

	plugboard.set_plugboard("test");

	Enigma rotor1;

	rotor1.set_rotor("test2");

	return 0;
}
