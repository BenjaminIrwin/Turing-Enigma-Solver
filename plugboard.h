#ifndef PLUGBOARD_H 
#define PLUGBOARD_H

#include <iostream>
#include <fstream>

class Plugboard 
{
private:	
	int plugboard[26];
	int plugboard_size;

public:
	bool set_plugboard(char const filename[], int& error);

	void operate_plugboard(int &i);

};

#endif
