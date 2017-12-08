#include "Vector.h"

#include <math.h>


Vector::Vector(int x_val, int y_val)
{
	int x = x_val;
	int y = y_val;

	normalise();
}

Vector::~Vector()
{

}

void Vector::normalise()
{
	int magnitude = 1;
	magnitude = (sqrt(x*x + y*y));
	
	x = magnitude / x;
	y = magnitude / x;
}

void Vector::scalar(float scalar)
{
	x *= scalar;
	y *= scalar;
}

int Vector::get_x()
{
	return x;
}

int Vector::get_y()
{
	return y;
}

void Vector::set_x(int x_val)
{
	x = x_val;
}

void Vector::set_y(int y_val)
{
	y = y_val;
}