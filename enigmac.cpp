#include <iostream>
#include "enigmac.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "errors.h"
#include "helper.h"

using namespace std;

bool Enigma::set_enigma(int argc, char** argv, int& error)
{
	
//Read input
	if (argc < 4)
	{
		error = INSUFFICIENT_NUMBER_OF_PARAMETERS;
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions";
		return false;
	}

//Load plugboard
	if (!(plugboard.set_plugboard(argv[1], error)))
	{
		return false;
	}

//Load reflector
	if (!(reflector.set_reflector(argv[2], error)))
	{
		return false;
	}

//Load rotors
	num_rotors = argc - 4;

	if (num_rotors > 0)
	{
		
		rotors = new Rotor[num_rotors];
		
		int j = 0;

		for (int i = num_rotors - 1; i >= 0; i-- )
		{
			
			if (!(rotors[j].set_rotor(argv[i + 3], error)))
			{
				return false;
			}
			
			j++;
	
		}
	}


//Load rotor positions
	int positions[num_rotors];

	if(!(fetch_rotor_pos(argv[argc - 1], num_rotors, positions, error)))
	{
		return false;
	}

//Load starting positions
	for (int i = 0 ; i < num_rotors ; i++)
	{
		rotors[i].calibrate_start_pos(positions, i, num_rotors);
	}

	return true;
}


bool Enigma::encrypt(istream& input, ostream& output, int& error)
{
	char letter;
	int letter_num;

	while (input >> ws >> letter && letter != '.')
	{
		if (letter < 64 || letter > 91)
		{
			cerr << endl << letter << " is an invalid input character (input characters must be upper case letters (A to Z)!" << endl;
			error = INVALID_INPUT_CHARACTER;
			return false;
		}

	letter_num = static_cast<int>(letter - 65);
	if(num_rotors > 0)
	{
		rotors[0].rotor_rotate();
		for (int i = 0 ; i < num_rotors - 1 ; i++)
		{
			if(rotors[i].notch)
			{
				rotors[i + 1].rotor_rotate();
				rotors[i].notch = false;
			}
		}
	}

	plugboard.operate_plugboard(letter_num);

	for (int i = 0 ; i < num_rotors ; i++)
	{
		letter_num = rotors[i].rtol(letter_num);
	}

	reflector.operate_reflector(letter_num);

	for (int i = num_rotors - 1 ; i >= 0 ; i--)
	{
		letter_num = rotors[i].ltor(letter_num);
	}

	plugboard.operate_plugboard(letter_num);
	
	letter = static_cast<char>(letter_num + 65);
	
	output << letter;

	}

	output << endl;	

	return true;
}

Enigma::~Enigma()
{
	if (num_rotors > 0)
	{
		delete [] rotors;
	}
}
