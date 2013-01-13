#include "StdAfx.h"
#include "GroundActor.h"

GroundActor::GroundActor(const String& SpritePath, const Bitmask * const mask, const Vector2& size)
	: CollidingActor(mask, size)
{
	SetSprite(SpritePath);

	SetFriction(1.0f);
	SetRestitution(0.0f);
	SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();
}

//void GroundActor::Update(float dt){
//}
//void GroundActor::Render(){
//}
//
//GroundActor::~GroundActor(void)
//{
//}
