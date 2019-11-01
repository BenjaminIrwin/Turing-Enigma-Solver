#include "enigma.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;
/*
void Enigma::input(int argv, char* argc[])
{
	if (argv < 4)
	{
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}
	
}
*/

bool Enigma::repetition_test (int num_array[], int array_pos)
{
//Checks all ints behind current one in array
//to see if previously appeared.
	
	for (int i = array_pos - 1; i >= 0; i--)
	{
		if(num_array[i] == num_array[array_pos])
		{
			return false;
		}
	}	

	return true;

}

bool Enigma::range_test(int num_array[], int array_pos)
{
//Checks if number is >=0 and < 26

	if(num_array[array_pos] < 0 || num_array[array_pos] > 25)
	{
		return false;
	} else
	{
		return true;
	}

}

bool Enigma::symbol_test(ifstream& input_file)
{

//Use .get to look three chars ahead
//If symbol then return error code
//Else return three slots back.

	for (int i = 1; i <= 3; i++)
	{
		char h;
		input_file.get(h);
		if (h == '\n' || input_file.eof())
		{
			input_file.seekg(-i, ios_base::cur);
			return true;
		} 

		if (h != ' ' && h != '-' && (h < 48 || h > 57))
		{
			return false;
		} 
		
	}
	
	input_file.seekg(-3, ios_base::cur); 
	return true;
}

bool Enigma::eof_test(ifstream& input_file)
{

	char c;
	int offset = input_file.tellg();
	input_file >> c;
	
	if(c == '\n' || input_file.eof())
	{
		return true;
	} 

	input_file.seekg(offset, ios_base::beg);
	return false;
}

int Enigma::set_plugboard(char const filename[])
{
	ifstream plugboard_file;
	plugboard_file.open(filename);
	if(plugboard_file.fail())
	{
		cout << "Plugboard open failed." << endl;		
	}

	//Empty file check
	if (eof_test(plugboard_file))
	{
		cout << "Plugboard file empty." << endl;
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(plugboard_file)) ; index++)
	{

		if(!(symbol_test(plugboard_file)))
		{
			cout << "Non numeric character found in plugboard file at index " 
			<< index << endl;	
			return NON_NUMERIC_CHARACTER;
		}


		plugboard_file >> plugboard[index];

		if (!(range_test(plugboard, index)))
		{
			cout << "Number out of range found in plugboard file at index " 
			<< index << endl;
			return INVALID_INDEX;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(plugboard, index)))
			{
				cout << "Repetition found in plugboard file at index " 
				<< index << endl;
				return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
			}
		}
	}	

	plugboard_size = index - 1;	

	//Return error if number of ints in file is over 26
	if (plugboard_size == 25 && !(eof_test(plugboard_file)))
	{
		cout << "Too many ints in file." << endl;
		plugboard_file.close();
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

		plugboard_file.close();

	//Return error if odd number of numbers read in index is -1 because of the extra iteration before
	//End is signalled.
	if (!(plugboard_size % 2))
	{
		cout << "Odd number of parameters" << endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}

	cout << "SUCCESS! File reads: " << endl;
	for (int j = 0; j < index; j++)
	{
		cout << plugboard[j] << endl;
	}

}

int Enigma::set_rotor(char const filename[])
{
	ifstream rotor_file;
	rotor_file.open(filename);
	if(rotor_file.fail())
	{
		cout << "Rotor open failed." << endl;		
	}

	//Empty file check
	if (eof_test(rotor_file))
	{
		cout << "Rotor file empty." << endl;
		rotor_file.close();	
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(rotor_file)) ; index++)
	{

		if(!(symbol_test(rotor_file)))
		{
			cout << "Non numeric character found in rotor file at index " 
			<< index << endl;//Note: this is wrong (index is one more)
			rotor_file.close();	
			return NON_NUMERIC_CHARACTER;
		}


		rotor_file >> rotor[index];

		if (!(range_test(rotor, index)))
		{
			cout << "Number out of range found in rotor file at index " 
			<< index << endl;
			rotor_file.close();	
			return INVALID_INDEX;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(rotor, index)))
			{
				cout << "Repetition found in rotor file at index " 
				<< index << endl;
				rotor_file.close();	
				return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
			}
		}
	}	

	//Return error if number of ints in file is under 26
	if (index < 26 && eof_test(rotor_file))
	{
		cout << "Insufficient number of rotors positions in file." << endl;
		rotor_file.close();
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}
	
	cout << "Success! Please read the rotor numbers below: " << endl;
	for (int j = 0; j < index; j++)
	{
		cout << rotor[j] << endl;
	}

	//This is where we deal with the notches.
	//First put them in an array of massive max size.
	//Then use a dynamic array to store however many there are.

	for (index = 0 ; index <= 25 && !(eof_test(rotor_file)) ; index++)
	{

		if(!(symbol_test(rotor_file)))
		{
			cout << "Non numeric character found in rotor file at index " 
			<< index << endl;
			rotor_file.close();	
			return NON_NUMERIC_CHARACTER;
		}

		rotor_file >> notches[index];

		if (!(range_test(notches, index)))
		{
			cout << "Number out of range found in rotor file at index " 
			<< index << endl;
			rotor_file.close();	
			return INVALID_INDEX;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(notches, index)))
			{
				cout << "Repetition found in rotor file at index " 
				<< index << endl;
				rotor_file.close();	
				return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
			}
		}
	}	

	if (index > 26)
	{
		cout << "Too many notches in file." << endl;
		rotor_file.close();
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

		rotor_file.close();

	num_notches = index - 1;

	cout << "Success! Please read the notch numbers below: " << endl;
	for (int j = 0; j < index; j++)
	{
		cout << notches[j] << endl;
	}


}

int Enigma::set_rotor_pos(char const filename[], int num_of_rotors)
{
	ifstream rotor_pos_file;
	rotor_pos_file.open(filename);
	if(rotor_pos_file.fail())
	{
		cout << "Rotor position file open failed." << endl;		
	}

	//Empty file check
	if (eof_test(rotor_pos_file))
	{
		cout << "Rotor position file empty." << endl;
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

	int index;

	int rotor_pos[num_of_rotors]; 

	for (index = 0 ; index < num_of_rotors && !(eof_test(rotor_pos_file)) ; index++)
	{
		
		if(!(symbol_test(rotor_pos_file)))
		{
			cout << "Non numeric character found in rotor_pos file at index " 
			<< index << endl;	
			return NON_NUMERIC_CHARACTER;
		}


		rotor_pos_file >> rotor_pos[index];

		if (!(range_test(rotor_pos, index)))
		{
			cout << "Number out of range found in rotor_pos file at index " 
			<< index << endl;
			return INVALID_INDEX;
		}
	}	

	if (index < num_of_rotors)
	{
		cout << "Too few values in rotor_pos file." << endl;
		rotor_pos_file.close();
		return INVALID_REFLECTOR_MAPPING;
	}

	//Return error if number of ints in file is over 26
	if (index == num_of_rotors && !(eof_test(rotor_pos_file)))
	{
		cout << "Too many ints in file." << endl;
		rotor_pos_file.close();
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

		rotor_pos_file.close();


	cout << "SUCCESS! File reads: " << endl;
	for (int j = 0; j < index; j++)
	{
		cout << rotor_pos[j] << endl;
	}

}

int Enigma::set_reflector(char const filename[])
{
	ifstream reflector_file;
	reflector_file.open(filename);
	if(reflector_file.fail())
	{
		cout << "Reflector open failed." << endl;		
	}

	//Empty file check
	if (eof_test(reflector_file))
	{
		cout << "Reflector file empty." << endl;
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(reflector_file)) ; index++)
	{

		if(!(symbol_test(reflector_file)))
		{
			cout << "Non numeric character found in reflector file at index " 
			<< index << endl;	
			return NON_NUMERIC_CHARACTER;
		}


		reflector_file >> reflector[index];

		if (!(range_test(reflector, index)))
		{
			cout << "Number out of range found in reflector file at index " 
			<< index << endl;
			return INVALID_INDEX;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(reflector, index)))
			{
				cout << "Repetition found in reflector file at index " 
				<< index << endl;
				return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
			}
		}
	}	

	if (index < 26)
	{
		cout << "Too few values in reflector file." << endl;
		reflector_file.close();
		return INVALID_REFLECTOR_MAPPING;
	}

	//Return error if number of ints in file is over 26
	if (index == 26 && !(eof_test(reflector_file)))
	{
		cout << "Too many ints in file." << endl;
		reflector_file.close();
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

		reflector_file.close();

	cout << "SUCCESS! File reads: " << endl;
	for (int j = 0; j < index; j++)
	{
		cout << reflector[j] << endl;
	}

}

