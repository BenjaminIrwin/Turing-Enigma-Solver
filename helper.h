#ifndef HELPER_H 
#define HELPER_H

#include <fstream>
#include <iostream>

using namespace std;
		
	bool fetch_rotor_pos(char const filename[], int num_of_rotors, int positions[], int& error);

	bool repetition_test(int num_array[], int array_pos, int& repeat_index);
	
	bool eof_test(ifstream& input_file);

	bool range_test(int num_array[], int array_pos);

	bool symbol_test(ifstream& input_file);

#endif
