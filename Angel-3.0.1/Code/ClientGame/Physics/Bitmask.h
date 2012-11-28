#pragma once
#include "Physics/Collision.h"
#include <list>
class Bitmask
{
private:
	 int m_x, m_y, m_type;
	 unsigned char * m_mask;
	 Vector2 m_scale;
	 float center(const float&) const;
public:
	Bitmask(const String&);
	int getX() const;
	int getY() const;
	int getType() const;
	Vector2 getScale() const;
	float getScaleX() const;
	float getScaleY() const;
	CollType checkCollition(const Vector2&, const Vector2&) const;
	std::list<Collision> getAllCollisions(const Vector2&, const Vector2&) const;
	std::list<CollType> getAllCollisionTypes(const Vector2&, const Vector2&) const;
	void setScale(const Vector2& size);
	void setScaleX(const float& scaleX);
	void setScaleY(const float& scaleY);
	void setSizeInWorldUnits(const Vector2&);
	void setSizeXInWorldUnits(const float&);
	void setSizeYInWorldUnits(const float&);

	unsigned char * getMask() const;
	void loadMask(const String&);
	~Bitmask(void);
};

