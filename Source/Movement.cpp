#include "Movement.h"

Movement::Movement(int direction)
{
	int chosen_dir = direction;

}

int Movement::get_dir_one()
{
	return direction_one;
}

int Movement::get_dir_two()
{
	return direction_two;
}

void Movement::set_dir_one(int input)
{
	 direction_one = input;
}

void Movement::set_dir_two(int input)
{
	direction_two = input;
}