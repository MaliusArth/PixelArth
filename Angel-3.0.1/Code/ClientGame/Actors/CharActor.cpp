#include "stdafx.h"
#include "CharActor.h"

#include "Infrastructure/Camera.h"
#include "Util/StringUtil.h"
#include "Util/MathUtil.h"
#include "Messaging/Switchboard.h"
#include "Util/DrawUtil.h"

//built-in loggers are pretty poor
#include "Infrastructure/Log.h"

#include "Physics\WorldCollision.h"
#include <iostream>

#define IDLE_TIME 5.0f

CharActor::CharActor(Bitmask* mask, float size)
	: _mask(mask)
	, _direction(SOUTH)
	, _moving(false)
	, _movingNorth(false)
	, _movingEast(false)
	, _movingSouth(false)
	, _movingWest(false)
	, _movementSpeed(0.05f)
	, _idleness(0.0f)
	, _idleAnim(false)
{
	//SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSize(size);
	_mask->setSizeInWorldUnits(size);

	//ClearSpriteInfo();
	SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");

	theSwitchboard.SubscribeTo(this, "CameraChange");
	theSwitchboard.SubscribeTo(this, "UpArrowPressed");
	theSwitchboard.SubscribeTo(this, "DownArrowPressed");
	theSwitchboard.SubscribeTo(this, "LeftArrowPressed");
	theSwitchboard.SubscribeTo(this, "RightArrowPressed");
	theSwitchboard.SubscribeTo(this, "UpArrowReleased");
	theSwitchboard.SubscribeTo(this, "DownArrowReleased");
	theSwitchboard.SubscribeTo(this, "LeftArrowReleased");
	theSwitchboard.SubscribeTo(this, "RightArrowReleased");
}

void CharActor::Update(float dt)
{
	float delay = 0.1f;
	spriteAnimationType animType = SAT_None;
	int startFrame = 0;
	int endFrame = 0;
	String animName = String();

	Vector2 direction = Vector2::Zero;
	if(_movingNorth)
	{
		direction.Y += 1.0f;
	}
	if(_movingEast)
	{
		direction.X += 1.0f;
	}
	if(_movingSouth)
	{
		direction.Y -= 1.0f;
	}
	if(_movingWest)
	{
		direction.X -= 1.0f;
	}
	direction != Vector2::Zero ? _moving=true : _moving=false;
	if(_moving)
	{
		float angle_rad = MathUtil::AngleFromVector(direction);
		//bug fix along axes:
		direction.X = direction.X == 0 ? 0 : _movementSpeed*cos(angle_rad);
		direction.Y = direction.Y == 0 ? 0 : (_movementSpeed/2)*sin(angle_rad);
	}
	Vector2 newPosition = _position + direction;
	
	//TEST
	Bitmask* world = new Bitmask("Resources/Images/coll.png");

	//multiple color bits in bitmask
	//unsigned int collType = thePixelArthGame.m_wColl->isColliding(*_mask, newPosition-(GetSize()/2));
	//if(collType > 0)
	std::list<CollType> collList = thePixelArthGame.m_collChecker->checkCollisions(Vector2::Zero, *world, newPosition, *_mask);
	std::cout << collList.size() << std::endl;

	bool collType = false;

	if(_moving & !collType)
	//if(_moving & collList has only c_none)
	{
		#pragma region Walk North
		if((newPosition.Y > _position.Y) & (newPosition.X == _position.X))
		{
			_idleness=0.0f;
			_direction = NORTH;
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
		if((newPosition.X > _position.X) & (newPosition.Y > _position.Y))
		{
			_idleness=0.0f;
			_direction = NORTHEAST;
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
		if((newPosition.X > _position.X) & (newPosition.Y == _position.Y))
		{
			_idleness=0.0f;
			_direction = EAST;
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
		if((newPosition.X > _position.X) & (newPosition.Y < _position.Y))
		{
			_idleness=0.0f;
			_direction = SOUTHEAST;
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
		if((newPosition.Y < _position.Y) & (newPosition.X == _position.X))
		{
			_idleness=0.0f;
			_direction = SOUTH;
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
		if((newPosition.X < _position.X) & (newPosition.Y < _position.Y))
		{
			_idleness=0.0f;
			_direction = SOUTHWEST;
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
		if((newPosition.X < _position.X) & (newPosition.Y == _position.Y))
		{
			_idleness=0.0f;
			_direction = WEST;
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
		if((newPosition.X < _position.X) & (newPosition.Y > _position.Y))
		{
			_idleness=0.0f;
			_direction = NORTHWEST;
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
	/*else if(collType == 0)	//make enum for collType
	{
		
	}*/

	if(!_moving | collType)
	{
		_idleness+=dt;
		if(_idleness < IDLE_TIME)
		{
			if(!_idleAnim)
			{
				switch(_direction)
				{
				case NORTH:
					if(_currentAnimName.compare("LookAroundUp") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						//CLAMPMODES: GL_CLAMP or GL_REPEAT
						//FILTERMODES: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, or 
						//GL_LINEAR_MIPMAP_LINEAR
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUp/lookAroundUp_00.png"/*, 0, GL_CLAMP, GL_LINEAR_MIPMAP_NEAREST*/);
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
			_idleness=0.0f;
			switch(_direction)
			{
			case NORTH:
				if(_currentAnimName.compare("LookAroundUp") != 0)
				{
					_idleAnim = true;
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
					_idleAnim = true;
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
					_idleAnim = true;
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
					_idleAnim = true;
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
					_idleAnim = true;
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
					_idleAnim = true;
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
					_idleAnim = true;
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
					_idleAnim = true;
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

	if(_moving & !collType)
	{
		_position = newPosition;		//TODO: check for memory leak
	}

	Actor::Update(dt);
}


void CharActor::AnimCallback(String animName)
{
	_currentAnimName = "";
	//only if idle animation
	_idleAnim = false;
	/*if(animName.compare("LookAroundDown") == 0)
	{

	}*/
}

void CharActor::ReceiveMessage(Message* m)
{
	if (m->GetMessageName() == "CameraChange")
	{
	}

#pragma region Animation Ended messages

	/*if (m->GetMessageName() == "Standing")
	{
		std::cout << "Standing" << std::endl;
	}*/

#pragma endregion
	
#pragma region Key-Down messages

	if (m->GetMessageName() == "UpArrowPressed")
	{
		//SystemLog().Log("UpArrowPressed");
		_movingNorth = true;
	}
	if (m->GetMessageName() == "DownArrowPressed")
	{
		_movingSouth = true;
	}
	if (m->GetMessageName() == "LeftArrowPressed")
	{
		_movingWest = true;
	}
	if (m->GetMessageName() == "RightArrowPressed")
	{
		_movingEast = true;
	}

#pragma endregion

#pragma region Key-Up messages

	if (m->GetMessageName() == "UpArrowReleased")
	{
		//SystemLog().Log("UpArrowReleased");
		_movingNorth = false;
	}
	if (m->GetMessageName() == "DownArrowReleased")
	{
		_movingSouth = false;
	}
	if (m->GetMessageName() == "LeftArrowReleased")
	{
		_movingWest = false;
	}
	if (m->GetMessageName() == "RightArrowReleased")
	{
		_movingEast = false;
	}

#pragma endregion

}

const BoundingBox& CharActor::GetBoundingBox() const
{
	return _bBox; 
}
