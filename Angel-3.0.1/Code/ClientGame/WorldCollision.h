#pragma once
#include <fstream>
#include "Vector.h"
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
	bool isCollideing(const Vector&,const Vector&) const;
	~WorldCollision(void);
};

