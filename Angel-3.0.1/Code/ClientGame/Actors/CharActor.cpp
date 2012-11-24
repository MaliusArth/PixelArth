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

CharActor::CharActor(Bitmask* mask)
	: _movingUp(false)
	, _movingDown(false)
	, _movingLeft(false)
	, _movingRight(false)
	, _mask(mask)
	, _movementSpeed(0.05f)
	, _idleness(0.0f)
	, _isStandingSet(true)
{
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSize(2.0f);

	//ClearSpriteInfo();
	SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
	/*
	LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
	PlaySpriteAnimation(
		0.2f,					//amount of time between frames
		SAT_Loop,				//other options are SAT_PingPong and SAT_OneShot
		0,				//starting frame
		8,				//ending frame
		"StandDown"		//name of the animation so you can get the event when it finishes
	);
	*/

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
	/*
	///Movement Try: 1
	Vector2 newPosition = _position;
	if(_movingUp){
		newPosition.Y += _movementSpeed;
	}
	if(_movingDown){
		newPosition.Y -= _movementSpeed;
	}
	if(_movingLeft){
		newPosition.X -= _movementSpeed;
	}
	if(_movingRight){
		newPosition.X += _movementSpeed;
	}
	char fsb1[256],fsb2[256] ;
    sprintf(fsb1, "%f", _position.X);
    sprintf(fsb2, "%f", newPosition.X);

	SystemLog().Log("_position: ");
	SystemLog().Log(fsb1);
	SystemLog().Log(" ");
	SystemLog().Log("newPosition: ");
	SystemLog().Log(fsb2);
	SystemLog().Log("\n");

	if(_position != newPosition){
		MoveTo(newPosition, 0.05f, true);
		//SetPosition(MathUtil::SmoothStep(_position, newPosition, 0.05f));
	}*/
	
	///Movement Try: 2
	/*if(_movingUp){
		_position.Y += (_movementSpeed/2);
	}
	if(_movingDown){
		_position.Y -= (_movementSpeed/2);
	}
	if(_movingLeft){
		_position.X -= _movementSpeed;
	}
	if(_movingRight){
		_position.X += _movementSpeed;
	}*/

	float delay = 0.1f;
	spriteAnimationType animType = SAT_None;
	int startFrame = 0;
	int endFrame = 0;
	String animName = String();

	///Movement Try: 3 (with collision)
	Vector2 newPosition(_position);

	if(_movingUp)
	{
		newPosition.Y += (_movementSpeed/2);
	}
	if(_movingDown)
	{
		newPosition.Y -= (_movementSpeed/2);
	}
	if(_movingLeft)
	{
		newPosition.X -= _movementSpeed;
	}
	if(_movingRight)
	{
		newPosition.X += _movementSpeed;
	}

	//std::cout << "newPosition: " << newPosition.X << " " << newPosition.Y << " Size: " << GetSize().X << " " << GetSize().Y
	//	<< " nPos+Size/2: "<< (newPosition+(GetSize()/2)).X << " " << (newPosition+(GetSize()/2)).Y << std::endl;
	
	//multiple color bits in bitmask
	//unsigned int collType = thePixelArthGame.m_wColl->isColliding(*_mask, newPosition-(GetSize()/2));
	//if(collType > 0)
	bool collType = thePixelArthGame.m_wColl->isColliding(*_mask, newPosition-(GetSize()/2));

	if(!collType)
	{
		///WalkUp
		if((newPosition.Y > _position.Y) & (newPosition.X == _position.X))
		//if(_movingUp & !_movingLeft & !_movingRight & !_movingDown)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkUp") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/up/walkUp_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUp";
			}
		}
		///WalkDown
		if((newPosition.Y < _position.Y) & (newPosition.X == _position.X))
		//if(_movingDown & !_movingLeft & !_movingRight & !_movingUp)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkDown") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/down/walkDown_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;
				animName = "WalkDown";
			}
		}
		///WalkLeft
		if((newPosition.X < _position.X) & (newPosition.Y == _position.Y))
		//if(_movingLeft & !_movingUp & !_movingDown & !_movingRight)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkLeft") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/left/walkLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;
				animName = "WalkLeft";
			}
		}
		///WalkRight
		if((newPosition.X > _position.X) & (newPosition.Y == _position.Y))
		//if(_movingRight & !_movingUp & !_movingDown & !_movingLeft)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkRight") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/right/walkRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkRight";
			}
		}
		///WalkUpRight
		if((newPosition.X > _position.X) & (newPosition.Y > _position.Y))
		//if(_movingRight & !_movingUp & !_movingDown & !_movingLeft)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkUpRight") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/upRight/walkUpRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUpRight";
			}
		}
		///WalkDownRight
		if((newPosition.X > _position.X) & (newPosition.Y < _position.Y))
		//if(_movingRight & !_movingUp & !_movingDown & !_movingLeft)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkDownRight") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/downRight/walkDownRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkDownRight";
			}
		}
		///WalkUpLeft
		if((newPosition.X < _position.X) & (newPosition.Y > _position.Y))
		//if(_movingRight & !_movingUp & !_movingDown & !_movingLeft)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkUpLeft") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/upLeft/walkUpLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUpLeft";
			}
		}
		///WalkDownLeft
		if((newPosition.X < _position.X) & (newPosition.Y < _position.Y))
		//if(_movingRight & !_movingUp & !_movingDown & !_movingLeft)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("WalkDownLeft") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/downLeft/walkDownLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkDownLeft";
			}
		}
	}
	/*else if(collType == 0)	//make enum for collType
	{
		
	}*/

	if(newPosition == _position | collType)
	//if((!_movingUp & !_movingDown & !_movingLeft & !_movingRight) | collType)
	{
		_idleness+=dt;
		if(_idleness < 5.0f)
		{
			if((_currentAnimName.compare("LookAroundDown") != 0) & !_isStandingSet)
			{	
				_isStandingSet = true;
				ClearSpriteInfo();
				_currentAnimName = "";
				//CLAMPMODES: GL_CLAMP or GL_REPEAT
				//FILTERMODES: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, or 
				//GL_LINEAR_MIPMAP_LINEAR
				SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png"/*, 0, GL_CLAMP, GL_LINEAR_MIPMAP_NEAREST*/);
			}
		}
		else if(_idleness >= 5.0f)
		{
			_idleness=0.0f;
			if(_currentAnimName.compare("LookAroundDown") != 0)
			{
				_isStandingSet = false;
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
				delay = 0.2f;
				animType = SAT_OneShot;
				startFrame = 0;
				endFrame = 9;
				animName = "LookAroundDown";
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

	if(!collType)
	{
		_position = newPosition;		//TODO: check for memory leak
	}

	Actor::Update(dt);
}


void CharActor::AnimCallback(String animName)
{
	_currentAnimName = "";
	if(animName.compare("LookAroundDown") == 0)
	{

	}
}

void CharActor::ReceiveMessage(Message* m)
{
	if (m->GetMessageName() == "CameraChange")
	{
	}

#pragma region Animation Ended messages

	if (m->GetMessageName() == "Standing")
	{
		std::cout << "Standing" << std::endl;
	}

#pragma endregion
	
#pragma region Key-Down messages

	if (m->GetMessageName() == "UpArrowPressed")
	{
		//SystemLog().Log("UpArrowPressed");
		_movingUp = true;
	}
	if (m->GetMessageName() == "DownArrowPressed")
	{
		_movingDown = true;
	}
	if (m->GetMessageName() == "LeftArrowPressed")
	{
		_movingLeft = true;
	}
	if (m->GetMessageName() == "RightArrowPressed")
	{
		_movingRight = true;
	}

#pragma endregion

#pragma region Key-Up messages

	if (m->GetMessageName() == "UpArrowReleased")
	{
		//SystemLog().Log("UpArrowReleased");
		_movingUp = false;
	}
	if (m->GetMessageName() == "DownArrowReleased")
	{
		_movingDown = false;
	}
	if (m->GetMessageName() == "LeftArrowReleased")
	{
		_movingLeft = false;
	}
	if (m->GetMessageName() == "RightArrowReleased")
	{
		_movingRight = false;
	}

#pragma endregion

}

const BoundingBox& CharActor::GetBoundingBox() const
{
	return _bBox; 
}
