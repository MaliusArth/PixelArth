
/** @file */
#pragma once

#include "Actors/Actor.h"

#include "Physics\WorldCollision.h"
#include "PixelArthGameManager.h"

enum Direction {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT};

/// An Actor for displaying game characters on the screen.
/**
 * A CharActor handles drawing text to the screen using world coordinates. The
 *  basis text rendering functions operate in screen-space, which can be annoying
 *  if you want to have debug data or labels for your Actors. 
 * 
 * In addition, a CharActor supports wraps up more functionality than the simple 
 *  text rendering, allowing varying alignments, newlines, etc. 
 */
class CharActor : public Actor
{
public:
	/**
	 * The constructor sets up all the information that this CharActor will
	 *  use to draw itself to the screen. 
	 */
	explicit CharActor(Bitmask* mask);
	
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
	 * Since CharActors use their own methods of drawing, it can be difficult to 
	 *  determine what space they're covering. If you want to do any kind of logic
	 *  dealing with CharActor overlap, this is the way to get the BoundingBox
	 *  information. 
	 * 
	 * @return A BoundingBox describing the area covered by the CharActor in 
	 *   GL units (not pixels). 
	 */
	const BoundingBox& GetBoundingBox() const;

	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "CharActor"
	 */
	virtual const String GetClassName() const { return "CharActor"; }

private:
	
	BoundingBox _bBox;
	Bitmask* _mask;
	bool _movingUp;
	bool _movingDown;
	bool _movingLeft;
	bool _movingRight;
	float _movementSpeed;
	float _idleness;
	Direction _direction;
	bool _isStandingSet;
};
