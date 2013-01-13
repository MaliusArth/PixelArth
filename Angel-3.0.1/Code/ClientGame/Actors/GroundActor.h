#pragma once
#include "Actors\CollidingActor.h"

class GroundActor : public CollidingActor
{
public:
	GroundActor(const String& SpritePath, const Bitmask * const mask, const Vector2& size);
	/*virtual void Update(float dt);
	virtual void Render();*/
	//~GroundActor(void);
};