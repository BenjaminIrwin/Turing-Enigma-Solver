#ifndef PLUGBOARD_H 
#define PLUGBOARD_H

#include <iostream>
#include <fstream>

class Plugboard 
{
public:	
	int plugboard[26];
	int plugboard_size;

	bool set_plugboard(char const filename[], int& error);

	void operate_plugboard(char &i);

};

#endif
