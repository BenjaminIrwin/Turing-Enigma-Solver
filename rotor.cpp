#include "rotor.h"
#include "helper.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

bool Rotor::set_rotor(char const filename[], int& error)
{
	ifstream rotor_file;
	rotor_file.open(filename);
	if(rotor_file.fail())
	{
		cerr << "Rotor file " << filename << " open failed." << endl;
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	//Empty file check
	if (eof_test(rotor_file))
	{
		cerr << "Rotor file " << filename << " empty." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}

	int rotor_[26];

	int index, repeat_index = 0;

	for (index = 0 ; index <= 25 && !(eof_test(rotor_file)) ; index++)
	{

		if(!(symbol_test(rotor_file)))
		{
			cerr << "Non-numeric character in rotor file " << filename << "." << endl;
			rotor_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		rotor_file >> rotor_[index];

		if (!(range_test(rotor_, index)))
		{
			cerr << "Number out of range found in rotor file " << filename << "." << endl;
			rotor_file.close();
			error = INVALID_INDEX;
			return false;
		}

		if (index > 0)
		{
			if(!(repetition_test(rotor_, index, repeat_index)))
			{
				cerr << "Invalid mapping of input " << index << " to output " 
				<< rotor_[index] <<  " in " << filename << endl << ". Output " 
				<< rotor_[index] << " is already mapped to input " << repeat_index << "." << endl; 
				error = INVALID_ROTOR_MAPPING;
				return false;
			}
		}
	}

	//Return error if number of ints in file is under 26
	if (index < 26 && eof_test(rotor_file))
	{
		cerr << "Insufficient number of mappings in rotor file " << filename << "." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}

//	cerr << "Success! Please read the rotor numbers below: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cerr << rotor_[j] << endl;
//	}

	convert_rotor(rotor_);

	//This is where we deal with the notches.
	//First put them in an array of massive max size.
	//Then use a dynamic array to store however many there are.

	for (index = 0 ; index <= 25 && !(eof_test(rotor_file)) ; index++)
	{

		if(!(symbol_test(rotor_file)))
		{
			cerr << "Non-numeric character found in rotor file " << filename << "." << endl;
			rotor_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}

		rotor_file >> notches[index];

		if (!(range_test(notches, index)))
		{
			cerr << "Number out of range found in rotor file " << filename << "." << endl;
			rotor_file.close();
			error = INVALID_INDEX;
			return false;
		}

		if (index > 0)
		{
			if(!(repetition_test(notches, index, repeat_index)))
			{
				cerr << "Notch repetition found in rotor file " << filename << "." << endl;
				rotor_file.close();
				error = INVALID_ROTOR_MAPPING;
				return false;
			}
		}
	}

	if (index > 26)
	{
		cerr << "Too many notch parameters in rotor file " << filename << "." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}

		rotor_file.close();

	num_notches = index;

//	cerr << "Success! Please read the notch numbers below: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cerr << notches[j] << endl;
//	}

	return true;

}

void Rotor::rotor_rotate()
{
	forwards_rotor_rotate();
	backwards_rotor_rotate();

	for (int i = 0 ; i < num_notches ; i++)
	{
		if (notches[i] == mapping[0][0])
		{	
			//cerr << "!" << endl;
			notch = true;
		}
	}
}

void Rotor::forwards_rotor_rotate()
{
//Convert this into a shuffle up for TWO DIMENSIONAL array.
	int temp1 = mapping[0][0], temp2 = mapping[0][1];

	for (int i = 0; i < 25; i++)
	{
		mapping[i][0] = mapping[i + 1][0];
		mapping[i][1] = mapping[i + 1][1];
	}

	mapping[25][0] = temp1;
	mapping[25][1] = temp2;
}


void Rotor::backwards_rotor_rotate()
{
	int temp1 = mapping_backwards[0][0], temp2 = mapping_backwards[0][1];

	for (int i = 0; i < 25; i++)
	{
		mapping_backwards[i][0] = mapping_backwards[i + 1][0];
		mapping_backwards[i][1] = mapping_backwards[i + 1][1];
	}

	mapping_backwards[25][0] = temp1;
	mapping_backwards[25][1] = temp2;

}

void Rotor::convert_rotor(int rotor_[])
{

	//Fill
	for (int i = 0; i <= 25; i++)
	{
		mapping[i][0] = i;
		//cerr << mapping[i][0] << "  ";
		mapping[i][1] = rotor_[i];
		//cerr << mapping[i][1] << "  " << endl;
	}

	create_backwards_mapping();

	

}

void Rotor::calibrate_start_pos(int positions[], int rotor_index, int num_rotors)
{

	while (mapping[0][0] != positions[(num_rotors - 1) - rotor_index])
	{
		rotor_rotate();
	}

	while (mapping_backwards[0][1] != positions[(num_rotors - 1) - rotor_index])
	{
		backwards_rotor_rotate();
	}
}

char Rotor::rtol(int i)
{
	int x, j = mapping[i][1];

	for (x = 0 ; x <= 25 && mapping[x][0] != j; x++);

	//cerr << "Letter maps to " << j << " OR " << o << endl;
	return x;
}

char Rotor::ltor(int i)
{

	int x, j = mapping_backwards[i][0];

	for (x = 0 ; x <= 25 && mapping_backwards[x][1] != j; x++);

	//cerr << "Letter maps to " << j << " OR " << o << endl;
	return x;
}

void Rotor::create_backwards_mapping()
{

	for (int j = 0 ; j <= 25 ; j++)
	{
		mapping_backwards[j][0] = mapping[j][0];
		mapping_backwards[j][1] = mapping[j][1];
	}

	sort_backwards_mapping();

}

void Rotor::sort_backwards_mapping()
{
	int smallest_index;
	for(int i = 0; i < 26; i++)
	{
		smallest_index = next_smallest_index(i);
		int temp1 = mapping_backwards[i][0];
		int temp2 = mapping_backwards[i][1];
		mapping_backwards[i][0] = mapping_backwards[smallest_index][0];
		mapping_backwards[i][1] = mapping_backwards[smallest_index][1];

		mapping_backwards[smallest_index][0] = temp1;
		mapping_backwards[smallest_index][1] = temp2;
	}

}


int Rotor::next_smallest_index(int start_index)
{
	int min = mapping_backwards[start_index][1], min_index = start_index;

	for (int i = start_index + 1; i < 26; i++)
	{
		if (mapping_backwards[i][1] < min)
		{
			min = mapping_backwards[i][1];
			min_index = i;
		}
	}

	return min_index;
}
