#pragma once
#include <fstream>
#include <math.h>
#include "Bitmask.h"
#define SCREEN_X 800
#define SCREEN_Y 600
class WorldCollision
{
private:
	Bitmask *m_world;
public:
	//constructor
	//param: Bitmap file path
	WorldCollision(const String&);
	bool isColliding(const Bitmask&, const Vector2&) const;
	//checks colission
	//param: begin of the checked area, end of the checked area
	//return: true if there IS a collision
	bool isColliding(const Vector2&,const Vector2&) const;
	~WorldCollision(void);
};

