#pragma once
//#include "PixelArthGameManager.h"
//#include "Physics\Bitmask.h"
#include "Physics\CollisionHandler.h"

class CollidingActor : public PhysicsActor
{
public:
	explicit CollidingActor(const Bitmask * const argMask, const Vector2 argSize = (-1.0f));

    inline Bitmask * const GetMask() const { return m_mask; }

    void SetLayered(const bool = true);

    inline bool IsLayered() const { return m_layered; }

	void SetColliding(const bool = true);
	
    inline bool IsColliding() const { return m_colliding; }

    virtual void Collide(const CollFlags& collFlags);

    virtual void Update(float dt);

    virtual void ReceiveMessage(Message* message);

protected:
    bool m_layered;
    bool m_colliding;
	CollFlags m_collFlags;
	Bitmask *m_mask;
};