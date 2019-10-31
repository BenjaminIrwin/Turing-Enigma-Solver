#include "enigma.h"
#include <fstream>

void Enigma::input(int argv, char* argc[])
{
	if (argv < 4)
	{
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}
	
}

bool Enigma::even_number_test(int number, int& error)
{
	if (!(number % 2))
	{
		return true;
	} else
	{
		return false;
	}
}

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

bool Engima::range_test(int num_array[], int array_pos)
{
//Checks if number is >=0 and < 26

	if(num_array[array_pos] < 0 || num_array[array_pos] > 26)
	{
		return false;
	} else
	{
		return true;
	}

}

bool Enigma::symbol_check(ifstream& input_file)
{

//Use .get to look three chars ahead
//If symbol then return error code
//Else return three slots back.
	for (int i = 1; i = 3; i++)
	{
		char h;
		plugboard_file.get(h);
		if (plugboard_file.eof)
		{
			plugboard_file.seekg(-i);
			return true;
		} else if (!(h < 48 || h > 57))
		{
			return false;
		} 
	}
		
	plugboard_file.seekg(-3); //Or -4, investigate.
	return true;

}

void Enigma::set_plugboard(char* filename)
{
	ifstream plugboard_file;
	plugboard_file.open(filename);

	int index = 0;
	bool break = false;

	int plugboard[30];

	if(!(symbol_check(plugboard_file)))
	{
		return NON_NUMERIC_CHARACTER;
	}

	for (index = 0 ; index < 26 ; index++)
	{

		plugboard_file >> plugboard[i];

		if(plugboard_file.eof())
		{
			goto end;
		}

		if (!(range_test(plugboard, i))
		{
			return INVALID_INDEX;
		}
		
		if (i > 0) 
		{
			if(!(repetition_test(plugboard, i)))
			{
				return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
			}
		}

		if(!(symbol_check(plugboard_file)))
		{	
			return NON_NUMERIC CHARACTER;
		}
	}	
	
	end:

	plugboard_file.close();

	//Return error if number of ints in
	//array steps over 26
	if (index > 25)
	{
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}

	//Return error if odd number of numbers read in
	if (!(index % 2))
	{
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}


}

