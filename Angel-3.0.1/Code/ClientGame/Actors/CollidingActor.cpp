#include "stdafx.h"
#include "CollidingActor.h"
#include <assert.h>
 CollidingActor::CollidingActor(const Bitmask * argMask,const  Vector2 argSize)
 {
	 
	 assert(mask != nullptr);
    m_mask = new Bitmask(*mask);
    m_mask->m_original_mask = mask;
	//SetName("Arth");
	//SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSize(argSize.X, argSize.Y);
    m_mask->setSize(argSize);

	SetDensity(1.0f);
	SetFriction(0.0f);
	SetRestitution(0.0f);
	SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();
 }

 void CollidingActor::SetColliding(const bool argColl)
 {
	 m_isColliding=argColl;
 }

 bool CollidingActor::IsColliding() const
 {
	 return m_isColliding;
 }