/////////////////////////////////////////////////////////////////////////
// PixelArth
// Copyright (C) 2012  Viktor Was <viktor.was@technikum-wien.at>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "CollidingActor.h"

CollidingActor::CollidingActor(const Bitmask * const argMask, const Vector2 argSize)
    : PhysicsActor()
    , m_colliding(false)
{
    assert(argMask != nullptr);
    m_mask = new Bitmask(*argMask);
    m_mask->m_original_mask = argMask;

    SetSize(argSize.X, argSize.Y);
    m_mask->setSize(argSize);

    SetLayered();

	SetIsSensor(true);
	SetFixedRotation(true);
}

void CollidingActor::SetLayered(const bool layered)
{
	m_layered = layered;
}

void CollidingActor::SetColliding(const bool argColl)
{
	m_colliding = argColl;
}

void CollidingActor::Collide(const CollFlags& collFlags)
{
    //would be much nicer with operator overloading but it's too late at night...
    m_collFlags.wall = collFlags.wall ? collFlags.wall : m_collFlags.wall;
    m_collFlags.floor = collFlags.floor ? collFlags.floor : m_collFlags.floor;
    m_collFlags.damage = collFlags.damage ? collFlags.damage : m_collFlags.damage;

    if(m_collFlags.damage!=0 || m_collFlags.floor!=0 || m_collFlags.wall!=0)
    {
        SetColliding();
    }
}

void CollidingActor::Update(float dt)
{
    m_collFlags = CollFlags();

	PhysicsActor::Update(dt);
}