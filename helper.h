#ifndef HELPER_H 
#define HELPER_H

#include <fstream>
#include <iostream>

using namespace std;

	bool repetition_test(int num_array[], int array_pos);
	
	bool eof_test(ifstream& input_file);

	bool range_test(int num_array[], int array_pos);

	bool symbol_test(ifstream& input_file);

#endif