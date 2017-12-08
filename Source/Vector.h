#pragma once
class Vector
{
public:
	Vector(int x, int y);
	~Vector();

	void normalise();
	void scalar(float scalar);

	int get_x();
	int get_y();
	void set_x(int x_val);
	void set_y(int y_val);



	float x_unit_vector = 1;
	float y_unit_vector = 1;


private:

	int x = 0;
	int y = 0;

};