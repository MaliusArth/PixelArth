/** @file */
#pragma once
#include "CollidingActor.h"
//#include "Physics\Bitmask.h"

//forward declaration - why isn't this needed in this particular case?
//class Bitmask;

enum Direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, NUM_DIRECTIONS};

/// An Actor for displaying game characters on the screen.
/**
 * A CharActor handles drawing text to the screen using world coordinates. The
 *  basis text rendering functions operate in screen-space, which can be annoying
 *  if you want to have debug data or labels for your Actors. 
 * 
 * In addition, a CharActor supports wraps up more functionality than the simple 
 *  text rendering, allowing varying alignments, newlines, etc. 
 */
class CharActor : public CollidingActor
{
public:
	/**
	 * The constructor sets up all the information that this CharActor will
	 *  use to draw itself to the screen. 
	 */
	explicit CharActor(const Bitmask * const mask, const Vector2& size = 2.0f);
	
	~CharActor(void);

	/**
	 * A function which makes the necessary updates to the Actor. The base 
	 *  implementation just updates the animations and intervals, but a 
	 *  subclass override can perform whatever extra magic is necessary. Make 
	 *  sure to call the base class's Update if you subclass. 
	 * 
	 * @param dt The amount of time that's elapsed since the beginning of the 
	 *   last frame. 
	 */
	virtual void Update(float dt);

    virtual void Collide(const CollFlags& collFlags);

	/**
	 * Override of the Renderable::Render function to draw text
	 */
	//virtual void Render();

	/**
	 * 
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
	 * Start simulating this PhysicsActor in the world. 
	 */
	//virtual void InitPhysics();
	
	/**
	 * If you want to have your own setup in a derived class, you can 
	 *  implement this function there. It's called at the end of the base
	 *  class's PhysicsActor::InitPhysics.
	 */
	//virtual void CustomInitPhysics() {}

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

private:
	//bool m_isKinematic;
	BoundingBox m_bBox;
	Direction m_direction;
	bool m_moving;
	bool m_movingNorth;
	bool m_movingEast;
	bool m_movingSouth;
	bool m_movingWest;
	float m_movementSpeed;
	float m_idleness;
	bool m_idleAnim;

	float m_timestampArrowReleased;
	///TEST
	//Bitmask* _world;
};
