#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <fstream>
#include "errors.h"

using namespace std;

class Enigma
{
public:	
	//void input (int argv, char* argc[]);

	bool even_number_test(int number, int& error);

	bool repetition_test(int num_array[], int array_pos);
	
	bool eof_test(ifstream& input_file);

	bool range_test(int num_array[], int array_pos);

	bool symbol_test(ifstream& input_file);

	int set_plugboard(char const filename[]);

	int set_rotor(char const filename[]);

/*
	void plugboard;

	void rotor;

	void reflector;

	void output;
*/

private:
	int plugboard[26];
	int plugboardIndex;

	int rotor[26];
	
};

#endif
