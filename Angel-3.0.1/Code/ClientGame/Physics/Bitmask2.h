#pragma once
#include "Physics/Collision.h"
class Bitmask2
{
private:
	  int m_sizeX, m_sizeY, m_type;
	 unsigned char * m_mask;
	 
public:
	//float center(const float&) const;
	Bitmask2();
	~Bitmask2();
	void copy(const Bitmask2&, const float& = 1, const float& = 1);
	void loadMask(const String&);
	int getSizeX() const;
	int getSizeY() const;
	int getType() const;
	//CollType checkCollition(const Vector2&, const Vector2&) const;
	/*void setScale(const unsigned int&, const unsigned int&);
	void setScaleX(const float& scaleX);
	void setScaleY(const float& scaleY);
	void setSizeInWorldUnits(const Vector2&);
	void setSizeXInWorldUnits(const float&);
	void setSizeYInWorldUnits(const float&);
	*/
	unsigned char * getMask() const;
	unsigned char getBit(const int&, const int&) const;
};

