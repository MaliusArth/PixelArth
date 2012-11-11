#pragma once
#include <fstream>
#include "Vector.h"
class WorldCollision
{
private:
	char* m_mask;
public:
	WorldCollision(String);
	bool isCollideing(Vector, Vector);
	~WorldCollision(void);
};

