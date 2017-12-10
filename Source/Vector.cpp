#include "Vector.h"

#include <math.h>


Vector::Vector(float x_val, float y_val)
{
	float x = x_val;
	float y = y_val;

	normalise();
}

Vector::~Vector()
{

}

void Vector::normalise()
{
	float magnitude = 1;
	magnitude = (sqrt(x*x + y*y));

	x /= magnitude;
	y /= magnitude;
}

void Vector::scalar(float scalar)
{
	x *= scalar;
	y *= scalar;
}

float Vector::get_x()
{
	return x;
}

float Vector::get_y()
{
	return y;
}

void Vector::set_x(float x_val)
{
	x = x_val;
}

void Vector::set_y(float y_val)
{
	y = y_val;
}