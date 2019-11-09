#include "helper.h"
#include "plugboard.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;
//This function operates the plugboard.
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
		cerr << "Plugboard file " << filename << " open failed." << endl;
		plugboard_file.close();
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(plugboard_file)) ; index++)
	{

		if(!(symbol_test(plugboard_file)))
		{
			cerr << "Non-numeric character in plugboard file " << filename << endl;
			plugboard_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		plugboard_file >> plugboard[index];

		if (!(range_test(plugboard, index)))
		{
			cerr << "Number out of range in plugboard file " << filename << endl; 
			plugboard_file.close();
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(plugboard, index)))
			{
				cerr << "Invalid mapping of input " << plugboard[index] 
				<< " in " << filename << endl; 
				plugboard_file.close();
				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
				return false;
			}
		}
	}	

	plugboard_size = index - 1;	

	//Return error if number of ints in file is over 26
	if (plugboard_size == 25 && !(eof_test(plugboard_file)))
	{
		cerr << "Too many mappings in plugboard file " << filename << endl;
		plugboard_file.close();
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

		plugboard_file.close();

	//Return error if odd number of numbers read in index is -1 because of the extra iteration before
	//End is signalled.
	if (!(plugboard_size % 2))
	{
		cerr << "Odd number of mappings in plugboard file " << filename << endl;
		plugboard_file.close();
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

	//cout << "SUCCESS! Plugboard file reads: " << endl;
	//for (int j = 0; j < index; j++)
	//{
	//	cout << plugboard[j] << endl;
	//}

	return true;
}


