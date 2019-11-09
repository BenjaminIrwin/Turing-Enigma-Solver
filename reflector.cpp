#include "reflector.h"
#include "helper.h"
#include "errors.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

void Reflector::operate_reflector(int &i)
{

	for (int a = 0; a <= 25; a++)
	{
		if (i == reflector[a])
		{
			if (a % 2)
			{
				
				i = (reflector[a - 1]);
				return;
			}

			if (!(a % 2))
			{
				i = (reflector[a + 1]);
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
		cerr << "Reflector file " << filename << " open failed." << endl;		
		error = ERROR_OPENING_CONFIGURATION_FILE;
		return false;
	}


	//Empty file check
	if (eof_test(reflector_file))
	{
		cerr << "Reflector file " << filename << " empty." << endl;
		reflector_file.close();
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		return false;
	}

	int index, repeat_index = 0;

	for (index = 0 ; index <= 26 && !(eof_test(reflector_file)) ; index++)
	{
		if(index <= 25)
		{
			if(!(symbol_test(reflector_file)))
			{
				cerr << "Non-numeric character in reflector file " << filename << "." << endl;
				reflector_file.close();	
				error = NON_NUMERIC_CHARACTER;
				return false;
			}


			reflector_file >> reflector[index];

			if (!(range_test(reflector, index)))
			{
				cerr << "Number out of range in reflector file " << filename << "." << endl;
				reflector_file.close();
				error = INVALID_INDEX;
				return false;
			}
			
			if (index > 0) 
			{
				if(!(repetition_test(reflector, index, repeat_index)))
				{
					cerr << "Invalid mapping of input " << reflector[index]
					<< " in " << filename << "." << endl;
					reflector_file.close();
					error = INVALID_REFLECTOR_MAPPING;
					return false;
				}
			}
		}
	}	

	if (index % 2)
	{
		cerr << "Incorrect (odd) number of mappings in reflector file " << filename << "." << endl;
		reflector_file.close();
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		return false;
	} else if (index < 26)
	{
		cerr << "Insufficient number of mappings in reflector file " << filename << "." << endl;
		reflector_file.close();
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;

	} else if (index > 26)
	{
		cerr << "Too many mappings in reflector file " << filename << "." << endl;
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
