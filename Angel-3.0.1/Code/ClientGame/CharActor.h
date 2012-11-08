
/** @file */
#pragma once

#include "Actors/Actor.h"

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
	 * The constructor sets up all the textual information that this CharActor will
	 *  use to draw itself to the screen. 
	 * 
	 * @param fontNickname the name of the font to be used when drawing this CharActor. 
	 *  The name of the font is set with the RegisterFont function. By default it uses
	 *  the monospaced font used in the Console, at 24 points. 
	 * @param displayString the actual text to be displayed
	 * @param align the desired alignment of the text
	 * @param lineSpacing the amount of space (in pixels) between each line of text
	 */
	CharActor();
	
	/**
	 * Override of the Renderable::Render function to draw text
	 */
	virtual void Render();
	
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
	//const BoundingBox& GetBoundingBox() const;
	
	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "CharActor"
	 */
	virtual const String GetClassName() const { return "CharActor"; }

private:
	
	BoundingBox _bBox;
};
