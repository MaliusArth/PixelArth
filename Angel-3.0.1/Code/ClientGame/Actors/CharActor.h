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
#include "Actors\CollidingActor.h"

enum Direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, NUM_DIRECTIONS};

/**
 * The CharActor/Protagonist class.
 */
class CharActor : public CollidingActor
{
public:
	/**
	 * The constructor sets up all the information that this CharActor will
	 *  use to draw itself to the screen.
	 * 
	 * @param mask One generic bitmask for pixel perfect collision.
	 * 
	 * @param argPosition Starting position.
	 * 
	 * @param size The size of the actor in GL units.
	 */
	explicit CharActor(const Bitmask * const mask, const Vector2& argPosition, const Vector2& size = 2.0f);
	
	~CharActor(void);

	/**
	 * A function which makes the necessary updates to the Actor.
	 * 
	 * @param dt The amount of time that's elapsed since the beginning of the 
	 *   last frame. 
	 */
	virtual void Update(float dt);

    /**
     * Changes char states on collision
     *  (Is called before Update)
     */
    virtual void Collide(const CollFlags& collFlags);

	/**
	 * Override of the Renderable::Render function to draw text
	 */
	virtual void Render();

	/**
     * Animation callback function
     *  Is called after an animation finishes and if a callback name is set
     * 
	 * @param animName animation name on which to respond.
     */
	virtual void AnimCallback(String animName);

	/**
	 * An implementation of the MessageListener interface, which listens for 
	 *  CameraChange messages and responds appropriately. 
	 * 
	 * @see MessageListener
	 * @param message The message getting delivered. 
	 */
	virtual void ReceiveMessage(Message* message);

	/**
	 * If you want to do any kind of logic dealing with CharActor overlap, 
     *  this is the way to get the BoundingBox information. 
	 * 
	 * @return A BoundingBox describing the area covered by the CharActor in 
	 *   GL units (not pixels). 
	 */
    const BoundingBox& CharActor::GetBoundingBox() const
    {
	    return m_bBox; 
    }

	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "CharActor"
	 */
	virtual const String GetClassName() const { return "CharActor"; }

    inline const bool IsDead() const { return m_dead; };
private:
	BoundingBox m_bBox;
	
    bool m_dead;

    // Orientation & movement
    Direction m_direction;
    Vector2 m_nextPosition;
	bool m_moving;
	bool m_movingNorth;
	bool m_movingEast;
	bool m_movingSouth;
	bool m_movingWest;
	float m_movementSpeed;
	
    // animation
    float m_idleness;
	bool m_idleAnim;
};
