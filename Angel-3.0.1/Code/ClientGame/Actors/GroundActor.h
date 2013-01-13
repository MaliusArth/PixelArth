#pragma once
#include "Actors\CollidingActor.h"

class GroundActor : public CollidingActor
{
public:
	GroundActor(const String& SpritePath, Bitmask * const mask);
	/*virtual void Update(float dt);
	virtual void Render();*/
	//~GroundActor(void);
};