#include "StdAfx.h"
#include "GroundActor.h"

GroundActor::GroundActor(const String& SpritePath, const Bitmask * const mask, const Vector2& pos, const Vector2& size)
	: CollidingActor(mask, size)
{
    SetSprite(SpritePath);    
    SetPosition(pos);
}
