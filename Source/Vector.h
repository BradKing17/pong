#pragma once
class Vector
{
public:
	Vector(float x, float y);
	~Vector();

	void normalise();
	void scalar(float scalar);

	float get_x();
	float get_y();
	void set_x(float x_val);
	void set_y(float y_val);


private:

	float x = 0;
	float y = 0;

};