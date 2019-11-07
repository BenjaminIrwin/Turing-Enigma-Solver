#include "enigma.h"
#include "helper.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

void Plugboard::operate_plugboard(char &i)
{

	for (int a = 0; a <= plugboard_size; a++)
	{
		if (i - 65 == plugboard[a])
		{
			if (a % 2)
			{
				
				i = (plugboard[a - 1] + 65);
				return;
			}

			if (!(a % 2))
			{
				i = (plugboard[a + 1] + 65);
				return;
			}
		}
	}

} 

void Reflector::operate_reflector(char &i)
{

	for (int a = 0; a <= 25; a++)
	{
		if (i - 65 == reflector[a])
		{
			if (a % 2)
			{
				
				i = (reflector[a - 1] + 65);
				return;
			}

			if (!(a % 2))
			{
				i = (reflector[a + 1] + 65);
				return;
			}
		}
	}

} 

bool Plugboard::set_plugboard(char const filename[], int& error)
{
	ifstream plugboard_file;
	plugboard_file.open(filename);
	if(plugboard_file.fail())
	{
		cout << "Plugboard open failed." << endl;
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	//Empty file check
	if (eof_test(plugboard_file))
	{
		cout << "Plugboard file empty." << endl;
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(plugboard_file)) ; index++)
	{

		if(!(symbol_test(plugboard_file)))
		{
//			cout << "Non numeric character found in plugboard file at index " 
//			<< index << endl;	
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		plugboard_file >> plugboard[index];

		if (!(range_test(plugboard, index)))
		{
//			cout << "Number out of range found in plugboard file at index " 
//			<< index << endl;
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(plugboard, index)))
			{
//				cout << "Repetition found in plugboard file at index " 
//				<< index << endl;
				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
				return false;
			}
		}
	}	

	plugboard_size = index - 1;	

	//Return error if number of ints in file is over 26
	if (plugboard_size == 25 && !(eof_test(plugboard_file)))
	{
//		cout << "Too many ints in file." << endl;
		plugboard_file.close();
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

		plugboard_file.close();

	//Return error if odd number of numbers read in index is -1 because of the extra iteration before
	//End is signalled.
	if (!(plugboard_size % 2))
	{
		cout << "Odd number of parameters" << endl;
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

//	cout << "SUCCESS! Plugboard file reads: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cout << plugboard[j] << endl;
//	}

	return true;
}

bool Rotor::set_rotor(char const filename[], int& error)
{
	ifstream rotor_file;
	rotor_file.open(filename);
	if(rotor_file.fail())
	{
		cout << "Rotor open failed." << endl;		
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	//Empty file check
	if (eof_test(rotor_file))
	{
		cout << "Rotor file empty." << endl;
		rotor_file.close();	
		error = INVALID_ROTOR_MAPPING;
		return false; 
	}

	int rotor_[26];

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(rotor_file)) ; index++)
	{

		if(!(symbol_test(rotor_file)))
		{
			cout << "Non numeric character found in rotor file at index " 
			<< index << endl;//Note: this is wrong (index is one more)
			rotor_file.close();	
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		rotor_file >> rotor_[index];

		if (!(range_test(rotor_, index)))
		{
			cout << "Number out of range found in rotor file at index " 
			<< index << endl;
			rotor_file.close();	
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(rotor_, index)))
			{
				cout << "Repetition found in rotor file at index " 
				<< index << endl;
				rotor_file.close();	
				error = INVALID_ROTOR_MAPPING;
				return false;
			}
		}
	}	

	//Return error if number of ints in file is under 26
	if (index < 26 && eof_test(rotor_file))
	{
		cout << "Insufficient number of rotors positions in file." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}
	
//	cout << "Success! Please read the rotor numbers below: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cout << rotor_[j] << endl;
//	}

	convert_rotor(rotor_);
		
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
			error = NON_NUMERIC_CHARACTER;
			return false;
		}

		rotor_file >> notches[index];

		if (!(range_test(notches, index)))
		{
			cout << "Number out of range found in rotor file at index " 
			<< index << endl;
			rotor_file.close();	
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(notches, index)))
			{
				cout << "Repetition found in rotor file at index " 
				<< index << endl;
				rotor_file.close();	
				error = INVALID_ROTOR_MAPPING;
				return false;
			}
		}
	}	

	if (index > 26)
	{
		cout << "Too many notches in file." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}

		rotor_file.close();

	num_notches = index;

//	cout << "Success! Please read the notch numbers below: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cout << notches[j] << endl;
//	}

	return true;

}


void Rotor::convert_rotor(int rotor_[])
{

	//Fill 
	for (int i = 0; i <= 25; i++)
	{
		mapping[i][0] = static_cast<char>(i + 65);
		mapping[i][1] = static_cast<char>(rotor_[i] + 65);
	}

	create_backwards_mapping();
	
}

bool fetch_rotor_pos(char const filename[], int num_of_rotors, int positions[], int& error)
{
	ifstream rotor_pos_file;
	rotor_pos_file.open(filename);
	if(rotor_pos_file.fail())
	{
		cout << "Rotor position file open failed." << endl;	
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;	
	}

	//Empty file check
	if (eof_test(rotor_pos_file))
	{
		cout << "Rotor position file empty." << endl;
		rotor_pos_file.close();
		error = NO_ROTOR_STARTING_POSITION;
		return false;
	}

	int index;

	for (index = 0 ; index < num_of_rotors && !(eof_test(rotor_pos_file)) ; index++)
	{
		
		if(!(symbol_test(rotor_pos_file)))
		{
			cout << "Non numeric character found in rotor_pos file at index " 
			<< index << endl;	
			rotor_pos_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		rotor_pos_file >> positions[index];

		if (!(range_test(positions, index)))
		{
			cout << "Number out of range found in rotor_pos file at index " 
			<< index << endl;
			rotor_pos_file.close();
			error = INVALID_INDEX;
			return false;
		}
	}	

	if (index < num_of_rotors)
	{
		cout << "Too few values in rotor_pos file." << endl;
		rotor_pos_file.close();
		error = NO_ROTOR_STARTING_POSITION;
		return false;
	}

	//Return error if number of ints in file is over 26, DO I NEED THIS?
	if (index == num_of_rotors && !(eof_test(rotor_pos_file)))
	{
		cout << "Too many ints in file." << endl;
		rotor_pos_file.close();
		error = INVALID_INDEX;
		return false;
	}

		rotor_pos_file.close();


//	cout << "SUCCESS! File reads: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cout << positions[j] << endl;
//	}

	return true;

}

void Rotor::calibrate_start_pos(int positions[], int rotor_index)
{	

	while (mapping[0][0] != static_cast<char>(positions[rotor_index] + 65))
	{
		rotor_rotate();	
	}
	
	while (mapping_backwards[0][1] != static_cast<char>(positions[rotor_index] + 65))
	{
		backwards_rotor_rotate();	
	}		
}

char Rotor::rtol(char i)
{
	char o, j = mapping[static_cast<int>(i - 65)][1];
	int x;

	for (x = 0 ; x <= 25 && mapping[x][0] != j; x++);

	o = static_cast<char>(x + 65);

	return o;
}

char Rotor::ltor(char i)
{
	char o, j = mapping_backwards[static_cast<int>(i - 65)][0];
	int x;

	for (x = 0 ; x <= 25 && mapping_backwards[x][1] != j; x++);

	o = static_cast<char>(x + 65);

	return o;
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
		char temp1 = mapping_backwards[i][0];
		char temp2 = mapping_backwards[i][1];
		mapping_backwards[i][0] = mapping_backwards[smallest_index][0];
		mapping_backwards[i][1] = mapping_backwards[smallest_index][1];

		mapping_backwards[smallest_index][0] = temp1;
		mapping_backwards[smallest_index][1] = temp2;
	}
				
}


int Rotor::next_smallest_index(int start_index)
{
	char min = mapping_backwards[start_index][1], min_index = start_index;
	
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



bool Reflector::set_reflector(char const filename[], int& error)
{
	ifstream reflector_file;
	reflector_file.open(filename);
	if(reflector_file.fail())
	{
		cout << "Reflector open failed." << endl;		
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}


	//Empty file check
	if (eof_test(reflector_file))
	{
		cout << "Reflector file empty." << endl;
		reflector_file.close();
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		return false;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(reflector_file)) ; index++)
	{

		if(!(symbol_test(reflector_file)))
		{
			cout << "Non numeric character found in reflector file at index " 
			<< index << endl;
			reflector_file.close();	
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		reflector_file >> reflector[index];

		if (!(range_test(reflector, index)))
		{
			cout << "Number out of range found in reflector file at index " 
			<< index << endl;
			reflector_file.close();
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(reflector, index)))
			{
				cout << "Repetition found in reflector file at index " 
				<< index << endl;
				reflector_file.close();
				error = INVALID_REFLECTOR_MAPPING;
				return false;
			}
		}
	}	

	if (index < 26)
	{
		cout << "Too few values in reflector file." << endl;
		reflector_file.close();
		error = INVALID_REFLECTOR_MAPPING;
		return false;
	}

	//Return error if number of ints in file is over 26
	if (index == 26 && !(eof_test(reflector_file)))
	{
//		cout << "Too many ints in file." << endl;
		reflector_file.close();
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		return false;
	}

		reflector_file.close();

//	cout << "SUCCESS! Reflector reads: " << endl;
//	for (int j = 0; j < index; j++)
//	{
//		cout << reflector[j] << endl;
//	}

	return true;

}

void Rotor::rotor_rotate()
{
	forwards_rotor_rotate();
	backwards_rotor_rotate();
	
	for (int i = 0 ; i < num_notches ; i++)
	{
		if (static_cast<int>(notches[i]) == mapping[0][0])
		{
			notch = true;
		}
	}
}

void notch_turn()
{
	//iterate through notches
	//if notch found at position
	//turn the next rotor by one
	
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
/*
void Rotor::ltor_rotor(int rotor[], char i)
{
	char o;

	int index = i - 65;
	o = rotor[index] + 65;
	return o;
}
*/
