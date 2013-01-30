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

#include "Infrastructure/Camera.h"
#include "Util/StringUtil.h"
#include "Util/MathUtil.h"
#include "Messaging/Switchboard.h"
#include "Util/DrawUtil.h"

#include "CharActor.h"
#include "PixelArthGameManager.h"
#include <iostream>

#define IDLE_TIME 5.0f

// TODO: Optimize: store all the character data like direction, movement states & rendering related variables into seperate data object

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
CharActor::CharActor(const Bitmask * const mask, const Vector2& argPosition ,const Vector2& size)
	: CollidingActor(mask, size)
	, m_direction(SOUTH)
	, m_moving(false)
	, m_movingNorth(false)
	, m_movingEast(false)
	, m_movingSouth(false)
	, m_movingWest(false)
	, m_movementSpeed(3.0f)
	, m_idleness(0.0f)
	, m_idleAnim(false)
    , m_dead(false)
{
	SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
    SetPosition(argPosition);

    m_bBox = BoundingBox(Vector2(GetPosition().X-(_size.X/2), GetPosition().Y-(_size.Y/2)),
                         Vector2(GetPosition().X+(_size.X/2), GetPosition().Y+(_size.Y/2)));
    //m_bBox.RenderBox();
    //m_bBox.RenderOutline();

	//theSwitchboard.SubscribeTo(this, "CameraChange");
	theSwitchboard.SubscribeTo(this, "UpArrowPressed");
	theSwitchboard.SubscribeTo(this, "DownArrowPressed");
	theSwitchboard.SubscribeTo(this, "LeftArrowPressed");
	theSwitchboard.SubscribeTo(this, "RightArrowPressed");
	theSwitchboard.SubscribeTo(this, "UpArrowReleased");
	theSwitchboard.SubscribeTo(this, "DownArrowReleased");
	theSwitchboard.SubscribeTo(this, "LeftArrowReleased");
	theSwitchboard.SubscribeTo(this, "RightArrowReleased");
}

/**
 * CharActor dtor
 * Unsubscribes from all messages
 * and deletes bitmask
 */
CharActor::~CharActor(void)
{
	//theSwitchboard.UnsubscribeFrom(this, "CameraChange");
    theSwitchboard.UnsubscribeFrom(this, "UpArrowPressed");
	theSwitchboard.UnsubscribeFrom(this, "DownArrowPressed");
	theSwitchboard.UnsubscribeFrom(this, "LeftArrowPressed");
	theSwitchboard.UnsubscribeFrom(this, "RightArrowPressed");
	theSwitchboard.UnsubscribeFrom(this, "UpArrowReleased");
	theSwitchboard.UnsubscribeFrom(this, "DownArrowReleased");
	theSwitchboard.UnsubscribeFrom(this, "LeftArrowReleased");
	theSwitchboard.UnsubscribeFrom(this, "RightArrowReleased");
    delete m_mask;
}

/**
 * Changes char states on collision
 * (is called before Update)
 */
void CharActor::Collide(const CollFlags& collFlags)
{
    // Collided with wall
    if(collFlags.wall && !m_collFlags.wall)
    {
        Vector2 temp;
        if (GetBody() != NULL)
        {
            temp = Vector2::Negate(Vector2(GetBody()->GetLinearVelocity().x, GetBody()->GetLinearVelocity().y));
        }
        GetBody()->SetLinearVelocity(b2Vec2(temp.X, temp.Y));
    }

    // Collided with snake
    if(m_collFlags.damage)
    {
        if(m_dead==false){
            std::cout << "Ouch!!!" << std::endl;
            theSwitchboard.Broadcast(new Message("Dead"));
        }
        m_dead = true;
    }

    CollidingActor::Collide(collFlags);
}

//
// Updates player states, movement, orientation etc.
// TODO: Optimize those redundant if's (consider a seperate data object for movement & orientation)
//
void CharActor::Update(float dt)
{
    // Update boundingbox position
    m_bBox.Min = Vector2(GetPosition().X-(_size.X/2), GetPosition().Y-(_size.Y/2));
    m_bBox.Max = Vector2(GetPosition().X+(_size.X/2), GetPosition().Y+(_size.Y/2));

    // Set orientation
	Vector2 direction = Vector2::Zero;
	if(m_movingNorth)
	{
		direction.Y += 1.0f;
	}
	if(m_movingEast)
	{
		direction.X += 1.0f;
	}
	if(m_movingSouth)
	{
		direction.Y -= 1.0f;
	}
	if(m_movingWest)
	{
		direction.X -= 1.0f;
	}
    direction != Vector2::Zero ? m_moving=true : m_moving=false;

	// Set movement speed according to orientation
    if(m_moving)
	{
        float angle_rad = MathUtil::AngleFromVector(direction);
        // conditional: bug fix along axes
        direction.X = direction.X == 0 ? 0 : (m_movementSpeed)*cos(angle_rad);
        direction.Y = direction.Y == 0 ? 0 : (m_movementSpeed/2)*sin(angle_rad);
        m_idleness = 0.0f;
	}
	
    // Set movement orientation
    m_nextPosition = _position + direction;
    if(m_moving)
	{
		if((m_nextPosition.Y > _position.Y) & (m_nextPosition.X == _position.X))
		{
			m_direction = NORTH;
		}
		else if((m_nextPosition.X > _position.X) & (m_nextPosition.Y > _position.Y))
		{
			m_direction = NORTHEAST;
		}
		else if((m_nextPosition.X > _position.X) & (m_nextPosition.Y == _position.Y))
		{
			m_direction = EAST;
		}
		else if((m_nextPosition.X > _position.X) & (m_nextPosition.Y < _position.Y))
		{
			m_direction = SOUTHEAST;
		}
		else if((m_nextPosition.Y < _position.Y) & (m_nextPosition.X == _position.X))
		{
			m_direction = SOUTH;
		}
		else if((m_nextPosition.X < _position.X) & (m_nextPosition.Y < _position.Y))
		{
			m_direction = SOUTHWEST;
		}
		else if((m_nextPosition.X < _position.X) & (m_nextPosition.Y == _position.Y))
		{
			m_direction = WEST;
		}
		else if((m_nextPosition.X < _position.X) & (m_nextPosition.Y > _position.Y))
		{
			m_direction = NORTHWEST;
		}
	}

    // Apply movement
    if(!m_collFlags.wall)
    {
        if (GetBody() != NULL)
        {
	        GetBody()->SetLinearVelocity(b2Vec2(direction.X, direction.Y));
        }
    }

	CollidingActor::Update(dt);
}

/**
 * Is called after an animation finishes and if a callback name is set
 */
void CharActor::AnimCallback(String animName)
{
	_currentAnimName = "";
	m_idleAnim = false;
}

/**
 * Reacts on all subscribed messages
 * (Is called before Update)
 */
void CharActor::ReceiveMessage(Message* m)
{
	
#pragma region Key-Down messages

	if (m->GetMessageName() == "UpArrowPressed")
	{
		m_movingNorth = true;
	}
	if (m->GetMessageName() == "DownArrowPressed")
	{
		m_movingSouth = true;
	}
	if (m->GetMessageName() == "LeftArrowPressed")
	{
		m_movingWest = true;
	}
	if (m->GetMessageName() == "RightArrowPressed")
	{
		m_movingEast = true;
	}

#pragma endregion

#pragma region Key-Up messages

	if (m->GetMessageName() == "UpArrowReleased")
	{
		m_movingNorth = false;
	}
	if (m->GetMessageName() == "DownArrowReleased")
	{
		m_movingSouth = false;
	}
	if (m->GetMessageName() == "LeftArrowReleased")
	{
		m_movingWest = false;
	}
	if (m->GetMessageName() == "RightArrowReleased")
	{
		m_movingEast = false;
	}

#pragma endregion

}

/**
 * Override from Actor::Render
 * Handles rendering
 */
void CharActor::Render()
{
    // Variable initializations
    float delay = 0.1f;
	spriteAnimationType animType = SAT_None;
	int startFrame = 0;
	int endFrame = 0;
	String animName = String();
    
    // Set animation for each movement direction
    if(m_moving && !m_collFlags.wall)
	{
		m_idleAnim = false;
	
		#pragma region Walk North
		if((m_nextPosition.Y > _position.Y) & (m_nextPosition.X == _position.X))
		{
			if(_currentAnimName.compare("WalkUp") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/up/walkUp_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUp";
			}
		}
		#pragma endregion Walk North
		#pragma region Walk North-East
		if((m_nextPosition.X > _position.X) & (m_nextPosition.Y > _position.Y))
		{
			if(_currentAnimName.compare("WalkUpRight") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/upRight/walkUpRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUpRight";
			}
		}
		#pragma endregion Walk North-East
		#pragma region Walk East
		if((m_nextPosition.X > _position.X) & (m_nextPosition.Y == _position.Y))
		{
			if(_currentAnimName.compare("WalkRight") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/right/walkRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkRight";
			}
		}
		#pragma endregion Walk East
		#pragma region Walk South-East
		if((m_nextPosition.X > _position.X) & (m_nextPosition.Y < _position.Y))
		{
			if(_currentAnimName.compare("WalkDownRight") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/downRight/walkDownRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkDownRight";
			}
		}
		#pragma endregion Walk South-East
		#pragma region Walk South
		if((m_nextPosition.Y < _position.Y) & (m_nextPosition.X == _position.X))
		{
			if(_currentAnimName.compare("WalkDown") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/down/walkDown_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;
				animName = "WalkDown";
			}
		}
		#pragma endregion Walk South
		#pragma region Walk South-West
		if((m_nextPosition.X < _position.X) & (m_nextPosition.Y < _position.Y))
		{
			if(_currentAnimName.compare("WalkDownLeft") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/downLeft/walkDownLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkDownLeft";
			}
		}
		#pragma endregion Walk South-West
		#pragma region Walk West
		if((m_nextPosition.X < _position.X) & (m_nextPosition.Y == _position.Y))
		{
			if(_currentAnimName.compare("WalkLeft") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/left/walkLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;
				animName = "WalkLeft";
			}
		}
		#pragma endregion Walk West
		#pragma region Walk North-West
		if((m_nextPosition.X < _position.X) & (m_nextPosition.Y > _position.Y))
		{
			if(_currentAnimName.compare("WalkUpLeft") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/upLeft/walkUpLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUpLeft";
			}
		}
		#pragma endregion Walk North-West
	}

    // Set idle animation
    if(!m_moving || m_collFlags.wall)
	{
        m_idleness+=theWorld.GetDT();
		if(m_idleness < IDLE_TIME)
		{
			if(!m_idleAnim)
			{
				switch(m_direction)
				{
				case NORTH:
					if(_currentAnimName.compare("LookAroundUp") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUp/lookAroundUp_00.png");
					}
					break;
				case NORTHEAST:
					if(_currentAnimName.compare("LookAroundUpRight") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUpRight/lookAroundUpRight_00.png");
					}
					break;
				case EAST:
					if(_currentAnimName.compare("LookAroundRight") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundRight/lookAroundRight_00.png");
					}
					break;
				case SOUTHEAST:
					if(_currentAnimName.compare("LookAroundDownRight") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDownRight/lookAroundDownRight_00.png");
					}
					break;
				case SOUTH:
					if(_currentAnimName.compare("LookAroundDown") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
					}
					break;
				case SOUTHWEST:
					if(_currentAnimName.compare("LookAroundDownLeft") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDownLeft/lookAroundDownLeft_00.png");
					}
					break;
				case WEST:
					if(_currentAnimName.compare("LookAroundLeft") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundLeft/lookAroundLeft_00.png");
					}
					break;
				case NORTHWEST:
					if(_currentAnimName.compare("LookAroundUpLeft") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUpLeft/lookAroundUpLeft_00.png");
					}
					break;
				}
			}
		}
		else
		{
			m_idleness=0.0f;
			m_idleAnim = true;
			switch(m_direction)
			{
			case NORTH:
				if(_currentAnimName.compare("LookAroundUp") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundUp/lookAroundUp_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundUp";
				}
				break;
			case NORTHEAST:
				if(_currentAnimName.compare("LookAroundUpRight") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundUpRight/lookAroundUpRight_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundUpRight";
				}
				break;
			case EAST:
				if(_currentAnimName.compare("LookAroundRight") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundRight/lookAroundRight_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundRight";
				}
				break;
			case SOUTHEAST:
				if(_currentAnimName.compare("LookAroundDownRight") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDownRight/lookAroundDownRight_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundDownRight";
				}
				break;
			case SOUTH:
				if(_currentAnimName.compare("LookAroundDown") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundDown";
				}
				break;
			case SOUTHWEST:
				if(_currentAnimName.compare("LookAroundDownLeft") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDownLeft/lookAroundDownLeft_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundDownLeft";
				}
				break;
			case WEST:
				if(_currentAnimName.compare("LookAroundLeft") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundLeft/lookAroundLeft_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundLeft";
				}
				break;
			case NORTHWEST:
				if(_currentAnimName.compare("LookAroundUpLeft") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundUpLeft/lookAroundUpLeft_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundUpLeft";
				}
				break;
			}
		}
	}

	if((_currentAnimName.compare(animName) != 0) & !IsSpriteAnimPlaying())
	{
		PlaySpriteAnimation(
			delay,					//amount of time between frames
			animType,				//other options are SAT_PingPong and SAT_OneShot
			startFrame,				//starting frame
			endFrame,				//ending frame
			animName.c_str()		//name of the animation so you can get the event when it finishes
		);
	}
    
    CollidingActor::Render();
}