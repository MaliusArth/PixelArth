#pragma once
#include "Actors\CollidingActor.h"

class GroundActor : public CollidingActor
{
public:
	GroundActor(const String& SpritePath, const Bitmask * const mask, const Vector2& pos, const Vector2& size=1.0f);
	/*virtual void Update(float dt);
	virtual void Render();*/
	//~GroundActor(void);
};