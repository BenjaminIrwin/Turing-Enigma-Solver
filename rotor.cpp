#include "rotor.h"
#include "helper.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

bool Rotor::set_rotor(char const filename[], int& error)
{
	ifstream rotor_file;//Open file
	rotor_file.open(filename);
	if(rotor_file.fail())//If error opening file
	{
		cerr << "Rotor file " << filename << " open failed." << endl;
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	if (eof_test(rotor_file))//Check if file empty
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

		if(!(symbol_test(rotor_file)))//Check for non-numeric chars
		{
			cerr << "Non-numeric character in rotor file " 
			<< filename << "." << endl;
			rotor_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		rotor_file >> rotor_[index];//Read in

		if (!(range_test(rotor_, index)))//Check number within range
		{
			cerr << "Number out of range found in rotor file " 
			<< filename << "." << endl;
			rotor_file.close();
			error = INVALID_INDEX;
			return false;
		}

		if (index > 0)//Check for repetition of read in numbers
		{
			if(!(repetition_test(rotor_, index, repeat_index)))
			{
				cerr << "Invalid mapping of input " << index 
				<< " to output " << rotor_[index] <<  " in " 
				<< filename << "." << endl << "Output " << 
				rotor_[index] << " is already mapped to input " 
				<< repeat_index << "." << endl; 
				error = INVALID_ROTOR_MAPPING;
				return false;
			}
		}
	}
	//Check if number of mappings is insufficient
	if (index < 26 && eof_test(rotor_file))
	{
		cerr << "Insufficient number of mappings in rotor file " 
		<< filename << "." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}

	if(!set_notches(filename, rotor_file, error))//Read in notches
		return false;

	convert_rotor(rotor_);//Form mapping and backwards_mapping


	return true;
}

bool Rotor::set_notches(char const filename[], ifstream& rotor_file, 
				int& error)
{
	int index, repeat_index = 0;

	//Read in notches
	for (index = 0 ; index <= 25 && !(eof_test(rotor_file)) ; index++)
	{

		if(!(symbol_test(rotor_file)))//Check for non-numeric symbols
		{
			cerr << "Non-numeric character found in rotor file " 
			<< filename << "." << endl;
			rotor_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}

		rotor_file >> notches[index];

		if (!(range_test(notches, index)))//Check if number within range
		{
			cerr << "Number out of range found in rotor file " 
			<< filename << "." << endl;
			rotor_file.close();
			error = INVALID_INDEX;
			return false;
		}

		if (index > 0)//Check for repetition of read in numbers
		{
			if(!(repetition_test(notches, index, repeat_index)))
			{
				cerr << "Notch repetition found in rotor file " 
				<< filename << "." << endl;
				rotor_file.close();
				error = INVALID_ROTOR_MAPPING;
				return false;
			}
		}
	}

	if (index > 26)//Check for extra notch mappings
	{
		cerr << "Too many notch parameters in rotor file " << filename 
		<< "." << endl;
		rotor_file.close();
		error = INVALID_ROTOR_MAPPING;
		return false;
	}

		rotor_file.close();

	num_notches = index;

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
			notch = true;
		}
	}
}

void Rotor::forwards_rotor_rotate()
{
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

	for (int i = 0; i <= 25; i++)
	{
		mapping[i][0] = i;
		mapping[i][1] = rotor_[i];
	}

	create_backwards_mapping();

	

}

void Rotor::calibrate_start_pos(int positions[], int rotor_index)
{

	while (mapping[0][0] != positions[rotor_index])
	{
		rotor_rotate();
	}

	while (mapping_backwards[0][1] != positions[rotor_index])
	{
		backwards_rotor_rotate();
	}

//	cout << "Rotors calibrated: " << endl << endl << endl;
//	for (int i = 0 ; i <= 25 ; i++)
//	{
//		cout << mapping[i][0] << " " << mapping[i][1] << " | " 
//		<< mapping_backwards[i][0] << " " << mapping_backwards[i][1] << endl;
//	}


}

char Rotor::rtol(int i)
{
	int x, j = mapping[i][1];

	for (x = 0 ; x <= 25 && mapping[x][0] != j; x++);

	return x;
}

char Rotor::ltor(int i)
{

	int x, j = mapping_backwards[i][0];

	for (x = 0 ; x <= 25 && mapping_backwards[x][1] != j; x++);

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
