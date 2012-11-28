#pragma once
#include <list>
#include "Physics/Collision.h"
#include "Physics/Bitmask.h"
class CollisionChecker{
public:
	CollisionChecker();
	std::list<CollType> checkCollissions(const Vector2&,const Bitmask&, const Vector2&, const Bitmask&) const;

};