#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>

class Enigma
{
	
	void input (int argv, char* argc[]);

	bool even_number_test(int number, int& error);

	bool repetition_test(int num_array[], int array_pos);

	bool range_test(int num_array[], int array_pos);

	bool symbol_check(ifstream& input_file);

	void set_plugboard(char* filename);
/*
	void plugboard;

	void rotor;

	void reflector;

	void output;
*/
private:
	//int plugboard[26];
	
}

#endif
