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
#include "PixelArthScreenCollisionTest.h"


PixelArthScreenCollisionTest::PixelArthScreenCollisionTest()
{
}

void PixelArthScreenCollisionTest::Start()
{

	//Creating a new, generic actor is simple. 
	a = new CharActor();
	
	//Sizes and coordinates are always in GL units, which can mean whatever you decide they mean
	// -- our physics packages (Box2D) assumes that they mean meters, though. 
	a->SetSize(2.0f); 
	
	//R, G, B, [A]
	//a->SetColor(0,0,0);

	a->SetColor(1,1,1,1); //(white and opaque so the texture comes through fully)
	//a->ClearSpriteInfo();
	a->SetSprite("Resources/Images/animations/chars/arth/standing.png");

	//We have to add it to the world for it to be drawn. All Actors implement Update and Render
	// methods that get called once per frame. All your logic should happen in the Update function,
	// and you should only implement Render if you have to do something out of the ordinary. 
	theWorld.Add(a);
	m_background= new GroundActor("Resources/Images/coll.png");
	theWorld.Add(m_background);




	//PixelArth housekeeping below this point. 
	#pragma region PixelArth Housekeeping
	t = new TextActor("Console", "Collision Test");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "PixelArthScreenCharTest.cpp");
	//fileLoc->SetPosition(MathUtil::ScreenToWorld(10, 563));
	//fileLoc->SetColor(.3f, .3f, .3f);
	//theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(a);
	#pragma endregion
}

void PixelArthScreenCollisionTest::Update(float dt)
{
	
}
