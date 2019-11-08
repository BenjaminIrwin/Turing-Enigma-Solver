#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>

using namespace std;

class Rotor
{
public:
	int starting_pos;
	char mapping[26][2];
	char mapping_backwards[26][2];
	int notches[26];
	int num_notches;
	bool notch = false;

	bool set_rotor(char const filename[], int& error);

	void rotor_rotate();

	void forwards_rotor_rotate();

	void convert_rotor(int rotor_[]);

	void calibrate_start_pos(int positions[], int rotor_index);

	char rtol(char i);

	char ltor(char i);

	int next_smallest_index(int start_index);

	void sort_backwards_mapping();

	void create_backwards_mapping();

	void backwards_rotor_rotate();	

};

#endif
