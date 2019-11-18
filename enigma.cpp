#include <iostream>
#include "enigma.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "errors.h"
#include "helper.h"

using namespace std;

bool Enigma::set_enigma(int argc, char** argv, int& error)
{
	if (argc < 4)//Check input
	{
		error = INSUFFICIENT_NUMBER_OF_PARAMETERS;
		cerr << "usage: enigma plugboard-file reflector-file"
		"(<rotor-file>)* rotor-positions";
		return false;
	}

	if (!(plugboard.set_plugboard(argv[1], error)))//Load plugboard
	{
		return false;
	}

	if (!(reflector.set_reflector(argv[2], error)))//Load reflector
	{
		return false;
	}

	num_rotors = argc - 4;

	if (num_rotors > 0)//Load rotors
	{
		rotors = new Rotor[num_rotors];
		
		int j = 0;

		for (int i = 0; i < num_rotors; i++)
		{
			if (!(rotors[j].set_rotor(argv[i + 3], error)))
			{
				return false;
			}
			
			j++;
		}
	}

	int positions[num_rotors];//Load rotor positions

	if(!(fetch_rotor_pos(argv[argc - 1], num_rotors, positions, error)))
	{
		return false;
	}

	for (int i = 0 ; i < num_rotors ; i++)//Calibrate starting positions
	{
		rotors[i].calibrate_start_pos(positions, i);
	}

	return true;
}

bool Enigma::fetch_rotor_pos(char const filename[], int num_of_rotors, 
				int positions[], int& error)
{
	ifstream rotor_pos_file;
	rotor_pos_file.open(filename);//Open file
	if(rotor_pos_file.fail())//If error opening file
	{
		cerr << "Rotor positions file " << filename << "." << endl;
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	if (eof_test(rotor_pos_file))//Check if file empty
	{
		cerr << "Insufficient number of parameters in rotor position "
		"file " << filename <<  "." << endl << "No starting position for"
		" rotor 0." << endl;
		rotor_pos_file.close();
		error = NO_ROTOR_STARTING_POSITION;
		return false;
	}

	int index;

	for (index = 0 ; index < num_of_rotors && !(eof_test(rotor_pos_file)) ; index++)
	{

		if(!(symbol_test(rotor_pos_file)))//Check for non-numeric symbols
		{
			cerr << "Non-numeric character in rotor positions file " 
			<< filename << "." << endl;
			rotor_pos_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}

		rotor_pos_file >> positions[index];//Read in

		if (!(range_test(positions, index)))//Check if number within range
		{
			cerr << "Number out of range in rotor positions file " 
			<< filename << "." << endl;
			rotor_pos_file.close();
			error = INVALID_INDEX;
			return false;
		}
	}

	if (index < num_of_rotors)//If fewer values than number of rotors
	{
		cerr << "Insufficient number of parameters in rotor positions "
		" file " << filename << "." << endl << "No starting position for "
		" rotor " << index << "." << endl;
		rotor_pos_file.close();
		error = NO_ROTOR_STARTING_POSITION;
		return false;
	}

	rotor_pos_file.close();
	return true;
}

bool Enigma::encrypt(istream& input, ostream& output, int& error)
{
	char letter;
	int letter_num;

	while (input >> ws >> letter && letter != '.')
	{
		if (letter < 64 || letter > 91)//Check if input valid
		{
			cerr << endl << letter << " is an invalid input "
			"character (input characters must be upper case letters "
			"(A to Z)!" << endl;
			error = INVALID_INPUT_CHARACTER;
			return false;
		}

	letter_num = static_cast<int>(letter - 65);
	
	if(num_rotors > 0)
	{
		rotors[0].rotor_rotate();
		for (int i = 0 ; i < num_rotors - 1 ; i++)//Check all rotors
		{
			if(rotors[i].notch)//If a notch is triggered
			{
				rotors[i + 1].rotor_rotate();//Rotate next
				rotors[i].notch = false;
			}
		}
	}

	plugboard.operate_plugboard(letter_num);//Operate plugboard 1st time

	for (int i = num_rotors - 1 ; i >= 0 ; i--)//Operate rotors right-left
	{
		letter_num = rotors[i].rtol(letter_num);
	}

	reflector.operate_reflector(letter_num);

	for (int i = 0 ; i < num_rotors ; i++)//Operate rotors left-right
	{
		letter_num = rotors[i].ltor(letter_num);
	}

	plugboard.operate_plugboard(letter_num);//Operate plugboard 2nd time
	
	letter = static_cast<char>(letter_num + 65);
	output << letter;

	}

	return true;
}

Enigma::~Enigma()
{
	if (num_rotors > 0)//Deallocate dynamic rotor array
	{
		delete [] rotors;
	}
}
