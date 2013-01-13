#include "stdafx.h"
#include <assert.h>
#include "CollidingActor.h"

CollidingActor::CollidingActor(Bitmask * const argMask, const Vector2 argSize)
{
    assert(argMask != nullptr);
    m_mask = new Bitmask(*argMask);
    m_mask->m_original_mask = argMask;
    //SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    SetSize(argSize.X, argSize.Y);
    m_mask->setSize(argSize);

    //m_collFlags = CollFlags();
}

void CollidingActor::SetColliding(const bool argColl)
{
	m_colliding = argColl;
}

void CollidingActor::Collide(const CollFlags& collFlags)
{
    m_collFlags = collFlags;
	//std::cout << "none: " << m_collFlags.none << std::endl;
 //   std::cout << "floor: " << m_collFlags.floor << std::endl;
 //   std::cout << "wall: " << m_collFlags.wall << std::endl;
    //m_collFlags.none = collFlags.none;
    //m_collFlags.floor = collFlags.floor;
    //m_collFlags.wall = collFlags.wall;
}

void CollidingActor::Update(float dt)
{
	PhysicsActor::Update(dt);
    /*
    if(GetBody() != NULL)
    {
        /// no need for collision messages...simply put this in CollidingActor::Update (CollidingActor::Update calls PhysicsActor::Update too)
        PhysicsActor *pa;
        CollidingActor *ca;
        b2ContactEdge* contactlist = GetBody()->GetContactList();
        
        while(contactlist != NULL)
        {
            pa = static_cast<PhysicsActor *>(contactlist->other->GetUserData());
            
            CollidingActor* ca = dynamic_cast<CollidingActor*>(pa);
            if (ca != NULL)
            {
                //CollisionHandler::checkCollision(
                std::cout << "char contacts with " << ca->GetName() << std::endl;
                contactlist = contactlist->next;
            }
        }
    }
    */
}

 void CollidingActor::ReceiveMessage(Message* m)
{
    /*std::cout << "CollidingActor recieved Msg: " << m->GetMessageName() << std::endl;

    if (m->GetMessageName() == "CollisionStartWith"+GetName())
    {
        m_colliding = true;
        std::cout << "coll test: " + GetName() << std::endl;
        //
        //TypedMessage<b2Contact*>* coll = dynamic_cast<TypedMessage<b2Contact*>*>(m);

        ////TypedMessage<b2Contact*>* coll = new TypedMessage<b2Contact*>(pa1Message, contact, pa2);
        //b2Contact* b2c = coll->GetValue();

        //CollidingActor* pa = static_cast<CollidingActor*>(b2c->GetFixtureA()->GetBody()->GetUserData());
        //CollidingActor* pb = static_cast<CollidingActor*>(b2c->GetFixtureB()->GetBody()->GetUserData());
        //
        //std::cout << "Test NameA: " << pa->GetName() << std::endl;
        //std::cout << "Test NameB: " << pb->GetName() << std::endl;
        //thePixelArthGame.m_collHandler->checkCollisions(pa->GetPosition(), pa->GetMask(), pb->GetPosition(), pb->GetMask());
        

        /// no need for collision messages...simply put this in CollidingActor::Update (CollidingActor::Update calls PhysicsActor::Update too)
        //CollidingActor *ca;
        //b2ContactEdge* contactlist = GetBody()->GetContactList();
        //while(contactlist!=NULL)
        //{
        //ca = static_cast<CollidingActor *>(contactlist->other->GetUserData());
        //std::cout << "char contacts with " << ca->GetName() << std::endl;
        //contactlist = contactlist->next;
        //}
    }
    */
 }