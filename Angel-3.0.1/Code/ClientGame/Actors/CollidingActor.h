#pragma once
//#include "PixelArthGameManager.h"
//#include "Physics\Bitmask.h"
#include "Physics\CollisionHandler.h"

class CollidingActor : public PhysicsActor
{
public:
	explicit CollidingActor(Bitmask * const argMask, const Vector2 argSize = (-1.0f));

    inline Bitmask * const GetMask() const { return m_mask; };

	void SetColliding(const bool = true);
	
    inline bool IsColliding() const
    {
        return m_colliding;
    };

    void SetCollFlags(const CollFlags& collFlags);

    virtual void Update(float dt);

    virtual void ReceiveMessage(Message* message);

protected:
    bool m_colliding;
	CollFlags m_collFlags;
	Bitmask *m_mask;
};