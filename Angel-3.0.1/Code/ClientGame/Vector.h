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
	int getX() const;
	void setX(const int);
	int getY() const;
	void setY(const int);
	~Vector(void);
};

