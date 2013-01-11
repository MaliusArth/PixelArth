#pragma once
//#include "PixelArthGameManager.h"
#include "Physics\Bitmask.h"

class CollidingActor : public PhysicsActor
{
public:
	explicit CollidingActor(Bitmask * const argMask, const Vector2 argSize = (-1.0f));

    const Bitmask* GetMask() const { return m_mask; }

	void SetColliding(const bool = true);
	
    bool IsColliding() const;

    virtual void Update(float dt);

protected:
	bool m_colliding;
	Bitmask *m_mask;
};