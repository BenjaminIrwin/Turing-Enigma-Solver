#include "helper.h"
#include "plugboard.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;
	
void Plugboard::operate_plugboard(int &i)
{
	for (int a = 0; a <= plugboard_size; a++)
	{
		if (i == plugboard[a])
		{
			if (a % 2)
			{
				
				i = (plugboard[a - 1]);
				return;
			}

			if (!(a % 2))
			{
				i = (plugboard[a + 1]);
				return;
			}
		}
	}
} 

bool Plugboard::set_plugboard(char const filename[], int& error)
{
	ifstream plugboard_file;//Open file
	plugboard_file.open(filename);
	if(plugboard_file.fail())//If error opening file
	{
		cerr << "Plugboard file " << filename << " open failed." 
		<< endl;
		plugboard_file.close();
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}

	int index, repeat_index = 0;

	for (index = 0 ; index <= 25 && !(eof_test(plugboard_file)) ; index++)
	{

		if(!(symbol_test(plugboard_file)))//Check for non-numeric chars
		{
			cerr << "Non-numeric character in plugboard file " 
			<< filename << "." << endl;
			plugboard_file.close();
			error = NON_NUMERIC_CHARACTER;
			return false;
		}

		plugboard_file >> plugboard[index];//Read in

		if (!(range_test(plugboard, index)))//Check number within range
		{
			cerr << "Number out of range in plugboard file " 
			<< filename << "." << endl; 
			plugboard_file.close();
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0)//Check for repetition of read in numbers
		{
			if(!(repetition_test(plugboard, index, repeat_index)))
			{
				cerr << "Invalid mapping of input " 
				<< plugboard[index] << " in " << filename 
				<< "." << endl; 
				plugboard_file.close();
				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
				return false;
			}
		}
	}	

	plugboard_size = index - 1;	
	//Check for extra mappings
	if (plugboard_size == 25 && !(eof_test(plugboard_file)))
	{
		cerr << "Too many mappings in plugboard file " << filename 
		<< "." << endl;
		plugboard_file.close();
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

	if (!(plugboard_size % 2))//Check if number of mappings is odd
	{
		cerr << "Odd number of mappings in plugboard file " 
		<< filename << "." << endl;
		plugboard_file.close();
		error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		return false;
	}

	plugboard_file.close();
	return true;
}
