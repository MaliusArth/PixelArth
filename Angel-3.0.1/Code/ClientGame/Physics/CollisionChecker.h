#pragma once
#include "Physics/Collision.h"
#include "Physics/Bitmask2.h"

enum PlayerState
{
 POISONED = 1 << 0,
 DEAD  = 1 << 1,
 JUMPING  = 1 << 2,
 RUNNING  = 1 << 3
};

struct CollFlags
{
	CollFlags(void)
	{
		floor= 0;
		wall= 0;
		none= 0;

	}
   unsigned int floor  : 1;    // 0..7   (3 bits)
   unsigned int wall : 1;    // 0..31  (6 bits)
   unsigned int none  : 1;    // 0..12  (5 bits)
};


class CollisionChecker{
public:
	
	//CollisionChecker();
	CollFlags checkCollisions(const Vector2&,const Bitmask2&, const Vector2&, const Bitmask2&) const;

};