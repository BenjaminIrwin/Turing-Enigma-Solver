#include "reflector.h"
#include "helper.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

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

bool Reflector::set_reflector(char const filename[], int& error)
{
	ifstream reflector_file;
	reflector_file.open(filename);
	if(reflector_file.fail())
	{
		cerr << "Reflector file open failed." << endl;		
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}


	//Empty file check
	if (eof_test(reflector_file))
	{
		cerr << "Reflector file empty." << endl;
		reflector_file.close();
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		return false;
	}

	int index;

	for (index = 0 ; index <= 25 && !(eof_test(reflector_file)) ; index++)
	{

		if(!(symbol_test(reflector_file)))
		{
			cerr << "Non-numeric character found in reflector file " << filename << endl;
			reflector_file.close();	
			error = NON_NUMERIC_CHARACTER;
			return false;
		}


		reflector_file >> reflector[index];

		if (!(range_test(reflector, index)))
		{
			cerr << "Number out of range in reflector file " << filename << endl;
			reflector_file.close();
			error = INVALID_INDEX;
			return false;
		}
		
		if (index > 0) 
		{
			if(!(repetition_test(reflector, index)))
			{
				cerr << "Repetition found in reflector file " << filename << endl;
				reflector_file.close();
				error = INVALID_REFLECTOR_MAPPING;
				return false;
			}
		}
	}	

	if (index < 26)
	{
		cerr << "Insufficient number of parameters in reflector file " << filename << endl;
		reflector_file.close();
		error = INVALID_REFLECTOR_MAPPING;
		return false;
	}

	//Return error if number of ints in file is over 26
	if (index == 26 && !(eof_test(reflector_file)))
	{
		cerr << "REFLECTOR: Too many ints in file." << endl;
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
