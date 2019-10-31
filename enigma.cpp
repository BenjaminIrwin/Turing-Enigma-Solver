#include "enigma.h"
#include <fstream>

Enigma::input(int argv, char* argc[])
{
	if (argv < 4)
	{
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}

	ifstream plugboard;
	plugboard.open(argc[1]);


	
}

Enigma::even_number_test(int number, int& error)
{
	if (!(number % 2))
	{
		return ERROR;
	}
}

void Enigma::repetition_test (int num_array[], int array_pos)
{
//Checks all ints behind current one in array
//to see if previously appeared.
	
	for (int i = array_pos - 1; i >= 0; i--)
	{
		if(num_array[i] == num_array[array_pos])
		{
			return ERROR;
		}
	}	

	return true;

}

void Engima::range_test(int num_array[], int array_pos)
{
//Checks if number is >=0 and < 26

	if(num_array[array_pos] < 0 || num_array[array_pos] > 26)
	{
		return ERROR;
	} else
	{
		return true;
	}

}

Enigma::check_number()
{
//Checks if character being read is numeric
//Needs to be called before range_test. 
}

Enigma::set_plugboard(char* filename)
{
	ifstream plugboard_file;
	plugboard_file.open(filename);

	plugboard.seekg(ios::end);
	int size = plugboard_file.tellg();
	plugboard_file.seekg(ios::beg);

	plugboard[0] = 1;

	for (int index = 0; index <= size && !plugboard_file.eof() && 
	range_test(plugboard[i]) && repetition_test(plugboard[i]); index++)
	{

		//Return error if index steps over 26
		if (index > 26)
		{
			return error;
		}

		//Use .get to look three chars ahead
		//If symbol then return error code
		//Else return three slots back.
		char h;
		for (int i = 0; i = 2; i++)
		{
			plugboard_file.get(h);
			if (!(h < 48 || h > 57))
			{
				return ERROR;
			} 
		}
		
		plugboard_file.seekg(-3); //Or -4, investigate.

		plugboard_file >> plugboard[i];
	}	
}

