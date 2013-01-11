#include "stdafx.h"
#include <assert.h>
#include "CollidingActor.h"
#include "Physics\CollisionHandler.h"

CollidingActor::CollidingActor(Bitmask * const argMask, const Vector2 argSize)
{
    assert(argMask != nullptr);
    m_mask = new Bitmask(*argMask);
    m_mask->m_original_mask = argMask;
    //SetName("Arth");
    //SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    SetSize(argSize.X, argSize.Y);
    m_mask->setSize(argSize);
 }

 void CollidingActor::SetColliding(const bool argColl)
 {
	 m_colliding=argColl;
 }

 bool CollidingActor::IsColliding() const
 {
	 return m_colliding;
 }

 void CollidingActor::Update(float dt)
 {
    PhysicsActor::Update(dt);
    if(GetBody()!=NULL)
    {
        /// no need for collision messages...simply put this in CollidingActor::Update (CollidingActor::Update calls PhysicsActor::Update too)
        CollidingActor *ca;
        b2ContactEdge* contactlist = GetBody()->GetContactList();
        while(contactlist != NULL)
        {
            ca = static_cast<CollidingActor *>(contactlist->other->GetUserData());
            
            std::cout << "char contacts with " << ca->GetName() << std::endl;
            contactlist = contactlist->next;
        }
    }
 }