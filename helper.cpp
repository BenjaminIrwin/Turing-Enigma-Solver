#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
#include "errors.h"

using namespace std;

bool repetition_test (int num_array[], int array_pos, int& repeat_index)
{
	for (int i = array_pos - 1; i >= 0; i--)
	{
		if(num_array[i] == num_array[array_pos])
		{
			repeat_index = i;
			return false;
		}
	}

	return true;
}

bool range_test(int num_array[], int array_pos)
{
	if(num_array[array_pos] < 0 || num_array[array_pos] > 25)
	{
		return false;
	} else
	{
		return true;
	}
}

bool symbol_test(ifstream& input_file)
{
	int position = input_file.tellg();
	string next;
	input_file >> next;

	for (int i = 0; i < int(next.length()) && !input_file.eof(); i++)
	{
		if(!isdigit(next[i]) && !(i == 0 && next[0] == '-'))
		{
			return false;
		}
	}

	input_file.seekg(position, ios_base::beg);
	return true;
}

bool eof_test(ifstream& input_file)
{

	char c = 0;
	int offset = input_file.tellg();
	input_file >> c;

	if(c == '\n' || input_file.eof())
	{
		return true;
	}

	input_file.seekg(offset, ios_base::beg);
	return false;
}

bool fetch_rotor_pos(char const filename[], int num_of_rotors, int positions[], int& error)
{
	ifstream rotor_pos_file;
	rotor_pos_file.open(filename);
	if(rotor_pos_file.fail())
	{
		cerr << "Rotor positions file " << filename << "." << endl;
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	if (eof_test(rotor_pos_file))
	{
		cerr << "Insufficient number of parameters in rotor positions file " << filename <<  "." << endl << "No starting position for rotor 0." << endl;
		rotor_pos_file.close();
		error = NO_ROTOR_STARTING_POSITION;
		return false;
	}

	int index;

	for (index = 0 ; index < num_of_rotors && !(eof_test(rotor_pos_file)) ; index++)
	{

		if(!(symbol_test(rotor_pos_file)))
		{
			cerr << "Non-numeric character in rotor positions file " << filename << "." << endl;
			rotor_pos_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		rotor_pos_file >> positions[index];

		if (!(range_test(positions, index)))
		{
			cerr << "Number out of range in rotor positions file " << filename << "." << endl;
			rotor_pos_file.close();
			error = INVALID_INDEX;
			return false;
		}
	}

	if (index < num_of_rotors)
	{
		cerr << "Insufficient number of parameters in rotor positions file " << filename << "." << endl << "No starting position for rotor " << index << "." << endl;
		rotor_pos_file.close();
		error = NO_ROTOR_STARTING_POSITION;
		return false;
	}

		rotor_pos_file.close();

	return true;
}
