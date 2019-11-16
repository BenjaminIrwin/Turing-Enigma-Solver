#ifndef PLUGBOARD_H 
#define PLUGBOARD_H

#include <iostream>
#include <fstream>

class Plugboard 
{
private:	
	int plugboard[26];
	int plugboard_size;

public:
	/*This function reads in from the configuration file 'filename' using
	an input stream and checks the legitimacy of the input. 
	
	It loads plugboard values into 'plugboard', and number of plugboard 
	values in 'plugboard_size'. If function encounters an error in user 
	input, int error will be altered and function returns false.*/
	bool set_plugboard(char const filename[], int& error);

	/*This function moves a specific value through the plugboard. Inputs 
	int 'i' by reference, the character to be encrypted/decrypted.

	Encrypts/decrypts 'i' according to plugboard mappings.*/
	void operate_plugboard(int &i);

};

#endif
