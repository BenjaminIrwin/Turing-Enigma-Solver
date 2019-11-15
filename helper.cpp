#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
#include "errors.h"

using namespace std;

bool repetition_test (int num_array[], int array_pos, int& repeat_index)
{
	for (int i = array_pos - 1; i >= 0; i--)
	{
		if(num_array[i] == num_array[array_pos])
		{
			repeat_index = i;
			return false;
		}
	}

	return true;
}

bool range_test(int num_array[], int array_pos)
{
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
	int position = input_file.tellg();
	string next;
	input_file >> next;

	for (int i = 0; i < int(next.length()) && !input_file.eof(); i++)
	{
		if(!isdigit(next[i]) && !(i == 0 && next[0] == '-'))
		{
			return false;
		}
	}

	input_file.seekg(position, ios_base::beg);
	return true;
}

bool eof_test(ifstream& input_file)
{

	char c = 0;
	int offset = input_file.tellg();
	input_file >> c;

	if(c == '\n' || input_file.eof())
	{
		return true;
	}

	input_file.seekg(offset, ios_base::beg);
	return false;
}
