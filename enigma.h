#ifndef ENIGMA_H 
#define ENIGMA_H

#include <iostream>
#include <fstream>
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

class Enigma
{
public:

	/*This function sets up the Enigma machine for use. Takes user input 
	('argc' and 'argv'). 
	
	Sets plugboard, reflector, optional rotor, notch and arrays according to 
	specification in input files. 

	If function encounters an error in user input, int error will be altered 
	and function returns false.*/
	bool set_enigma(int argc, char** argv, int& error);

	/*This function fetches the rotor positions and reads in the positions
	from 'filename'.

	Fills 'positions' with the positions.

	If function encounters an error in user input, int error will be altered
	and function returns false.*/		
	bool fetch_rotor_pos(char const filename[], int num_of_rotors, 
				int positions[], int& error);


	/*This function operates the Enigma machine. Takes input in form of a 
	message or encrypted message.
	
	Operates plugboard, reflector and optional rotor functions to output 
	an encrypted or decrypted message.

	If function encounters an error in user input, int error will be 
	altered and function returns false.*/
	bool encrypt(std::istream& input, std::ostream& output, int& error);

	/*This destructor deletes the dynamically allocated rotors array*/
	~Enigma();

private:
	Rotor* rotors;//Array of rotors
	int num_rotors = 0;//Number of rotors
	Plugboard plugboard;//Plugboard
	Reflector reflector;//Reflector
};


#endif
