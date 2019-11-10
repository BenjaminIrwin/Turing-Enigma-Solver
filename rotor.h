#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>

using namespace std;

class Rotor
{
private:
	int starting_pos;
	int mapping[26][2];
	int mapping_backwards[26][2];
	int notches[26];
	int num_notches;

	void forwards_rotor_rotate();

	void convert_rotor(int rotor_[]);

	int next_smallest_index(int start_index);

	void sort_backwards_mapping();

	void create_backwards_mapping();

	void backwards_rotor_rotate();	

public:
	bool set_rotor(char const filename[], int& error);

	void rotor_rotate();

	void calibrate_start_pos(int positions[], int rotor_index, int num_rotors);

	char rtol(int i);

	char ltor(int i);

	bool notch = false;
};

#endif
