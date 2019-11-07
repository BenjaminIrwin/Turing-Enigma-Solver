#include <iostream>
#include "enigma.h"
#include "errors.h"
#include "helper.h"
using namespace std;

int main (int argc, char* argv[]) 
{

//Read input

	int error = 0;

	if (argc < 4)
	{
		error = INSUFFICIENT_NUMBER_OF_PARAMETERS;
		return error;
	}

//Load plugboard

	Plugboard plugboard;
	plugboard.set_plugboard(argv[1], error);

//Load reflector

	Reflector reflector;
	reflector.set_reflector(argv[2], error);

//Load rotors

	int num_rotors = argc - 4;

	Rotor* rotors = new Rotor[num_rotors];	

	if (num_rotors > 0)
	{
		for (int i = 0; i < num_rotors; i++)
		{
			if (!(rotors[i].set_rotor(argv[i+3], error)))
			{
				return error;
			}
		}
	}


//Load rotor positions

	int positions[num_rotors];	

	if(!(fetch_rotor_pos(argv[argc - 1], num_rotors, positions, error)))
	{
		return error;
	}

//Load starting positions

		rotors[0].copy_mapping();
	cout << "Please find copied rotor below: " << endl;
	for (int i = 0 ; i <= 25 ; i++)
	{
		cout << rotors[0].mapping_backwards[i][0] << "   " << rotors[0].mapping_backwards[i][1] << endl;
	}


		rotors[0].selection_sort();
	
	cout << "Please find sorted rotor below: " << endl;
	for (int i = 0 ; i <= 25 ; i++)
	{
		cout << rotors[0].mapping_backwards[i][0] << "   " << rotors[0].mapping_backwards[i][1] << endl;
	}

	cout << rotors[0].rtol('F') << endl;

	cout << rotors[0].ltor('G') << endl;//THIS ISN'T WORKING

/*
//Cipher
	char i, o;

	input >> i;

	while (i != '.')
	{
		if (i < 64 || i > 91)
		{
			cout << i << "is an invalid input character." << endl;
			error = INVALID_INPUT_CHARACTER;
			return error;	
		}

		//Plugboard --> Rotor(s) (if any) --> Reflector --> Rotors --> Plugboard
		ouput << o;

		input >> i;
	}

	if (i == '.')
	{
		cout << "Program finished." << endl;
	}
	
	

	char i = 'Z', o;
	plugboard.operate_plugboard(i, o);
	cout << "Input maps to " << o << endl;

	i = 'O';
	o = 'A';
	reflector.operate_reflector(i, o);
	cout << "Input maps to " << o << endl;
*/

	return error;
}
