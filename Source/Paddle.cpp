#include "Paddle.h"

Paddle::Paddle(int direction)
{
	int chosen_dir = direction;

}

int Paddle::get_dir_one()
{
	return direction_one;
}

int Paddle::get_dir_two()
{
	return direction_two;
}

void Paddle::set_dir_one(int input)
{
	 direction_one = input;
}

void Paddle::set_dir_two(int input)
{
	direction_two = input;
}