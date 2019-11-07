#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <fstream>

using namespace std;

bool fetch_rotor_pos(char const filename[], int num_of_rotors, int positions[], int& error);

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
	int starting_pos;
	char mapping[26][2];
	char mapping_backwards[26][2];
	int notches[26];
	int num_notches;

	bool set_rotor(char const filename[], int& error);

	void rotor_rotate();

	void convert_rotor(int rotor_[]);

	void calibrate_start_pos(int positions[], int rotor_index);

	char rtol(char i);

	char ltor(char i);

	int next_smallest_index(int start_index);

	void selection_sort();

	void copy_mapping();


//	char ltor_rotor(int rotor[], char i);
};

#endif
