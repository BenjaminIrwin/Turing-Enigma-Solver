#ifndef HELPER_H 
#define HELPER_H

#include <fstream>
#include <iostream>

using namespace std;
	/*This function checks for repetition in a given int array*/	
	bool repetition_test(int num_array[], int array_pos, int& repeat_index);
	
	/*This function checks the upcoming space in a stream for the end of file*/
	bool eof_test(ifstream& input_file);

    /*This function checks if num_array[array_pos] is within range (0-25)*/
	bool range_test(int num_array[], int array_pos);

    /*This function checks the upcoming space in a stream for non-numeric 
    symbols*/
	bool symbol_test(ifstream& input_file);

#endif
