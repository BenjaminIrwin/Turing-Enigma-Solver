#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <fstream>

using namespace std;

class Plugboard 
{
public:	
	int plugboard[26];
	int plugboard_size;

	bool set_plugboard(char const filename[], int& error);

	void operate_plugboard(char i, char& o);

};

class Reflector
{
public:
	int reflector[26];

	bool set_reflector(char const filename[], int& error);

	void operate_reflector(char i, char& o);
};

class Rotor
{
public:
	int* rotor_pos;
	int rotor[26];
	int notches[26];
	int num_notches;

	bool set_rotor(char const filename[], int& error);

	bool fetch_rotor_pos(char const filename[], int num_of_rotors, int& error);

	void rotor_rotate(int rotor[]);

//	char ltor_rotor(int rotor[], char i);
};

#endif
