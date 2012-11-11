#pragma once
class Vector
{
private: 
	int m_x, m_y;
public:
	//Constructor:
	//param: x coordinate of vector, y coordinate of vector
	Vector(int, int);
	//simple setters/getters... i think they explain themselfs
	int getX();
	void setX(int);
	int getY();
	void setY(int);
	~Vector(void);
};

