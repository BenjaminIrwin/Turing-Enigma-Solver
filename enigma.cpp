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
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions";
		return error;
	}

//Load plugboard

	Plugboard plugboard;
	if (!(plugboard.set_plugboard(argv[1], error)))
	{
		return error;
	}

//Load reflector

	Reflector reflector;
	if (!(reflector.set_reflector(argv[2], error)))
	{
		return error;
	}

//Load rotors

	int num_rotors = argc - 4;
	Rotor* rotors;

	if (num_rotors > 0)
	{
		
		rotors = new Rotor[num_rotors];
		
		int j = 0;

		for (int i = num_rotors - 1; i >= 0; i-- )
		{
			
			if (!(rotors[j].set_rotor(argv[i + 3], error)))
			{
				return error;
			}
			
			j++;
	
		}
	}

//	for (int x = 0 ; x < 26 ; x++)
//	{
//
//		cout << x << ". " << rotors[3].mapping[x][0] << " " << rotors[3].mapping[x][1]
//		<< endl; 
//
//	}	

/*
	for (int x = 0; x < num_rotors; x++)
	{
		for (int i = 0 ; i < 26 ; i++)
		{

		cout << i << ". " << rotors[x].mapping[i][0] << "  " << rotors[i].mapping[i][1]
		<< endl;// << " | " << rotor[i].mapping 

		}	
	}
*/

//Load rotor positions

	int positions[num_rotors];

	if(!(fetch_rotor_pos(argv[argc - 1], num_rotors, positions, error)))
	{
		return error;
	}

//	for (int i = 0; i < num_rotors; i++)
//	{
//		cout << positions[i] << endl;
//	}


//Load starting positions

	for (int i = 0 ; i < num_rotors ; i++)
	{
		rotors[i].calibrate_start_pos(positions, i, num_rotors);
	}
/*
	for (int x = 0; x < num_rotors; x++)
	{
		for (int i = 0 ; i < 26 ; i++)
		{

		cout << i << ". " << rotors[x].mapping_backwards[i][0] << "  " << rotors[x].mapping_backwards[i][1]
		<< endl;// << " | " << rotor[i].mapping 
		
		}

		cout << "ROTATED ONE UP: " << endl;

		rotors[x].rotor_rotate();

		for (int i = 0 ; i < 26 ; i++)
		{

		
		cout << i << ". " << rotors[x].mapping_backwards[i][0] << "  " << rotors[x].mapping_backwards[i][1]
		<< endl;// << " | " << rotor[i].mapping 

		}	
	}
*/

	




//Cipher

	char letter;
	int letter_num;

	cout << endl;//Why do I need this?
	

	while (cin >> ws >> letter && letter != '.')
	{
		if (letter < 64 || letter > 91)
		{
			cerr << endl << letter << " is an invalid input character (input characters must be upper case letters (A to Z)!" << endl;
			error = INVALID_INPUT_CHARACTER;
			return error;
		}

	letter_num = static_cast<int>(letter - 65);
//	cout << "MAPPING [0][1] == " << rotors[0].mapping[0][1] << endl;
/*	
	for (int x = 0 ; x < 26 ; x++)
	{

		cout << x << ". " << rotors[0].mapping[x][0] << " " << rotors[0].mapping[x][1]
		<< endl; 

	}	
*/
	if(num_rotors > 0)
	{
		rotors[0].rotor_rotate();
		for (int i = 0 ; i < num_rotors - 1 ; i++)
		{
			if(rotors[i].notch)
			{
				//cout << "ALERT: NOTCH FOUND IN ROTOR " << i << endl;
				rotors[i + 1].rotor_rotate();
				rotors[i].notch = false;
			}
		}
	}

	plugboard.operate_plugboard(letter_num);

	for (int i = 0 ; i < num_rotors ; i++)
	{
		letter_num = rotors[i].rtol(letter_num);
//		cout << "Letter after forward rotor " << i << " is " << letter << endl;
	}

	reflector.operate_reflector(letter_num);
//	cout << "Letter after reflector is " << letter << endl;

	for (int i = num_rotors - 1 ; i >= 0 ; i--)
	{
		letter_num = rotors[i].ltor(letter_num);
//		cout << "Letter after backward rotor " << i << " is " << letter << endl;
	}

	plugboard.operate_plugboard(letter_num);
	
	letter = static_cast<char>(letter_num + 65);
	
	cout << letter;

	}

	cout << endl;	

	return error;
}
