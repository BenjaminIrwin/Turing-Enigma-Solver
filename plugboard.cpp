#include "helper.h"
#include "plugboard.h"
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
			cout << "Non numeric character found in plugboard file." << endl;
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		plugboard_file >> plugboard[index];

		if (!(range_test(plugboard, index)))
		{
			cout << "Number out of range found in plugboard file at index " 
			<< index << endl;
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(plugboard, index)))
			{
				cout << "Repetition found in plugboard file at index " 
				<< index << endl;
				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
				return false;
			}
		}
	}	

	plugboard_size = index - 1;	

	//Return error if number of ints in file is over 26
	if (plugboard_size == 25 && !(eof_test(plugboard_file)))
	{
		cout << "Too many parameters in plugboard file." << endl;
		plugboard_file.close();
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

		plugboard_file.close();

	//Return error if odd number of numbers read in index is -1 because of the extra iteration before
	//End is signalled.
	if (!(plugboard_size % 2))
	{
		cout << "Odd number of parameters in plugboard file." << endl;
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

	cout << "SUCCESS! Plugboard file reads: " << endl;
	for (int j = 0; j < index; j++)
	{
		cout << plugboard[j] << endl;
	}

	return true;
}

