#ifndef REFLECTOR_H 
#define REFLECTOR_H

#include <iostream>
#include <fstream>

class Reflector
{
private:
	int reflector[26];

public:
	/*This function reads in from the configuration file 'filename' using
	an input stream and checks the legitimacy of the input. 
	
	It loads plugboard values into 'reflector'. If function encounters 
	an error in user input, int error will be altered and function 
	returns false.*/
	bool set_reflector(char const filename[], int& error);

	/*This function moves a specific value through the reflector. Inputs 
	int 'i' by reference representing the character to be 
	encrypted/decrypted.

	Encrypts/decrypts 'i' according to 'reflector' mappings.*/
	void operate_reflector(int &i);
};

#endif
