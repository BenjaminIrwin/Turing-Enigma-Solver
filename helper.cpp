#include <iostream>
#include <fstream>
#include "helper.h"

using namespace std;

bool repetition_test (int num_array[], int array_pos)
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

bool range_test(int num_array[], int array_pos)
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

bool symbol_test(ifstream& input_file)
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

bool eof_test(ifstream& input_file)
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


