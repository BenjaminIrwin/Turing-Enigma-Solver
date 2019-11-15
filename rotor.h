#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>

using namespace std;

class Rotor
{
public:
	bool notch = false;

	/*This function reads in from the configuration file 'filename' using
	an input stream and checks the legitimacy of the input. 
	
	It loads rotor values into mapping, mapping_backwards and notches. If
	function encounters an error in user input, int error will be altered
	and function returns false.*/
	bool set_rotor(char const filename[], int& error);
	
	/*This function rotates the mapping and mapping_backwards arrays. 
	
	Function changes 'notch' to true if a notch value is encountered in 
	mapping[0][0] and mapping_backwards[0][1].*/
	void rotor_rotate();

	/*This function calibrates the rotor's start position according to the
	values in the 'positions' array. Inputs positions, rotor_index
	and num_rotors.

	Alters mapping and mapping_backwards such that their values align
	with the position in positions[rotor_index].*/
	void calibrate_start_pos(int positions[], int rotor_index, 
					int num_rotors);

	/*This function moves a specific value from right to left through the 
	rotor. Inputs an int representing the character to be 
	encrypted/decrypted.

	Outputs an int representing encrypted/decrypted character.*/
	char rtol(int i);
	
	/*This function moves a specific value from left to right through a 
	specific rotor. Inputs an int representing the character to be 
	encrypted/decrypted.

	Outputs an int representing encrypted/decrypted character.*/
	char ltor(int i);

private:
	int starting_pos;
	int mapping[26][2];
	int mapping_backwards[26][2];
	int notches[26];
	int num_notches;

	/*This function 'rotates' forward rotor array.

	Moves int values in mapping array down one index. Moves values in 
	*[0][0] to *[25][25]*/
	void forwards_rotor_rotate();

	/*This function converts the format of the inputted 'rotor_' array. 

	Alters mapping and mapping_backwards to contain rotor_ values in 2d
	array form.*/
	void convert_rotor(int rotor_[]);

	/*This function finds index of next smallest index above 'start_index' 
	in mapping_backwards array.

	Returns int value representing next smallest index.*/
	int next_smallest_index(int start_index);

	/*This function applies the selection sort algorithm to 
	mapping_backwards.

	Sorts mapping_backwards such that *[1][0] is the lowest integer between
	*[1][0] and *[1][26].*/
	void sort_backwards_mapping();

	/*This function copies mapping into mapping backwards swapping the 
	indices such that mapping[x][y] == mapping_backwards[y][x].*/
	void create_backwards_mapping();

	/*This function 'rotates' rotor array.

	Moves int values in mapping_backwards array down one index. Moves 
	values in *[0][0] to *[25][25]*/
	void backwards_rotor_rotate();	
};

#endif
