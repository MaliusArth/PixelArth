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

#pragma once

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

protected:
    bool m_layered;
    bool m_colliding;
	CollFlags m_collFlags;
	Bitmask *m_mask;
};