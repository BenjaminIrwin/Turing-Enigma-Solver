#ifndef REFLECTOR_H 
#define REFLECTOR_H

#include <iostream>
#include <fstream>

class Reflector
{
public:
	int reflector[26];

	bool set_reflector(char const filename[], int& error);

	void operate_reflector(int &i);
};

#endif
