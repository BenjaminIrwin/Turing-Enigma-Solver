#include <iostream>
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
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
	if (!(plugboard.set_plugboard(argv[1], error)))
	{
		return error;
	}
	cout << "Plugboard: " << flush;
	for (int i = 0 ; i < plugboard.plugboard_size ; i++)
	{
		cout << plugboard.plugboard[i] << " ";
	}

	cout << endl;


//Load reflector

	Reflector reflector;
	if (!(reflector.set_reflector(argv[2], error)))
	{
		return error;
	}
	cout << "Reflector: " << flush;
	for (int i = 0 ; i < 26 ; i++)
	{
		cout << reflector.reflector[i] << " ";
	}

	cout << endl;

//Load rotors

	int num_rotors = argc - 4;
	Rotor* rotors = new Rotor[num_rotors];
	if (num_rotors > 0)
	{
		for (int i = 0; i < num_rotors; i++)
		{
		//	cout << "Loading rotor " << i << endl;

			if (!(rotors[i].set_rotor(argv[i + 3], error)))
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
	cout << "Reflector positions: " << endl;
	for (int i = 0 ; i < num_rotors ; i++)
	{
		cout << positions[i] << " ";
	}
	
	cout << endl;

//Load starting positions

	for (int i = 0 ; i < num_rotors ; i++)
	{
		rotors[i].calibrate_start_pos(positions, i);
	}

//Cipher

	char letter;

	cout << "Please enter text here (end with a '.'): " << endl;

	cin >> ws >> letter;

	while (letter != '.' && !cin.eof())
	{
		if (letter < 64 || letter > 91)
		{
		//	cout << letter << "is an invalid input character." << endl;
			error = INVALID_INPUT_CHARACTER;
			return error;
		}

	rotors[0].rotor_rotate();
	for (int i = 0 ; i < num_rotors - 1 ; i++)
	{
		if(rotors[i].notch)
		{
			//cout << "ALERT: NOTCH FOUND IN ROTOR " << i << endl;
			rotors[i + 1].rotor_rotate();
		}
	}

	plugboard.operate_plugboard(letter);
//	cout << "After plugboard, letter is " << letter << endl;

	for (int i = 0 ; i < num_rotors ; i++)
	{
		letter = rotors[i].rtol(letter);
		//cout << "Letter after forward rotor " << i << " is " << letter << endl;
	}

	reflector.operate_reflector(letter);
//	cout << "Letter after reflector is " << letter << endl;

	for (int i = num_rotors - 1 ; i >= 0 ; i--)
	{
		letter = rotors[i].ltor(letter);
		//cout << "Letter after backward rotor " << i << " is " << letter << endl;
	}

	plugboard.operate_plugboard(letter);

	cout << letter;

	cin >> ws >> letter;
	}

	cout << endl;

	return error;
}
