//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2012, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

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

CharActor::CharActor(/*Bitmask* mask*/)
	: _movementSpeed(0.1f)
	, _movingUp(false)
	, _movingDown(false)
	, _movingLeft(false)
	, _movingRight(false)
	//, _mask(mask)
{
	SetColor(1.0f, 1.0f, 1.0f);

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

	///Movement Try: 3 (with collision)
	Vector2 newPosition(_position);

	if(_movingUp){
		newPosition.Y += (_movementSpeed/2);
	}
	if(_movingDown){
		newPosition.Y -= (_movementSpeed/2);
	}
	if(_movingLeft){
		newPosition.X -= _movementSpeed;
	}
	if(_movingRight){
		newPosition.X += _movementSpeed;
	}
	//std::cout << "newPosition: " << newPosition.X << " " << newPosition.Y << " Size: " << GetSize().X << " " << GetSize().Y
	//	<< " nPos+Size/2: "<< (newPosition+(GetSize()/2)).X << " " << (newPosition+(GetSize()/2)).Y << std::endl;
	if(!thePixelArthGame.m_wColl->isColliding(newPosition-(GetSize()/2), newPosition+(GetSize()/2)))
	{
		_position = newPosition;		//TODO: check for memory leak
	}
	
	Actor::Update(dt);
}

void CharActor::ReceiveMessage(Message* m)
{
	if (m->GetMessageName() == "CameraChange")
	{
	}
	
	//Key-down for movement
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

	//Key-up for movement
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
}

//const BoundingBox& CharActor::GetBoundingBox() const
//{
//	return _bBox; 
//}
