#include "StdAfx.h"
#include "Vector.h"


Vector::Vector(int argX, int argY)
{
	m_x=argX;
	m_y=argY;
}
int Vector::getX() const{
	return m_x;
}
	void Vector::setX(int arg){
		m_x= arg;
	}
	int Vector::getY() const{
		return m_y;
	}
	void Vector::setY(int arg){
		m_y=arg;
	}

Vector::~Vector(void)
{
}
