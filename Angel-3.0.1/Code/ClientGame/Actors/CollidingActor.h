#pragma once
#include "PixelArthGameManager.h"
class CollidingActor:public PhysicsActor{
public:
	CollidingActor(const Bitmask * argMask,const
		Vector2 argSize);
	void SetColliding(const bool = true);
	bool IsColliding() const;
private:
	bool m_isColliding;
	Bitmask *m_mask;
};