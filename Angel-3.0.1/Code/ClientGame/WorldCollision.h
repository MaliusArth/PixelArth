#pragma once
#include <fstream>
#include <math.h>
#define SCREEN_X 800
#define SCREEN_Y 600
class WorldCollision
{
private:
	unsigned char* m_mask;
public:
	//constructor
	//param: Bitmap file path
	WorldCollision(const String&);
	//checks colission
	//param: begin of the checked area, end of the checked area
	//return: true if there IS a collision
	bool isCollideing(const Vector2&,const Vector2&) const;
	~WorldCollision(void);
};

