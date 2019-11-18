#ifndef HELPER_H 
#define HELPER_H

#include <fstream>
#include <iostream>

using namespace std;
	/*This function checks if a number has been repeated in an array of 
	integers.

	Returns false if a repetition has been found, and changes repeat_index
	to the index of the repeated number.*/	
	bool repetition_test(int num_array[], int array_pos, int& repeat_index);
	
	/*This function checks the upcoming space for the end of file.

	Returns true if end of file has been reached.*/	 
	bool eof_test(ifstream& input_file);

	/*This function checks if an inputted number is within range (0 - 25).

	Returns false if num_array[array_pos] is outside this range.*/
	bool range_test(int num_array[], int array_pos);

	/*This function checks the input stream to examine whether the next
	characters to be read in are non-numeric.

	Returns false if a non-numeric digit is found.*/
	bool symbol_test(ifstream& input_file);

#endif
