#pragma once
class Movement
{
public:
	Movement(int direction);

	int get_dir_one();
	int get_dir_two();
	void set_dir_one(int direction);
	void set_dir_two(int direction);


private:

	int direction_one = 0;
	int direction_two = 0;


};