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
#include "PixelArthGameManager.h"

#if !ANGEL_MOBILE
	/*
	#include "PixelArthScreenStart.h"
	#include "PixelArthScreenInstructions.h"
	*/
	#include "WorldMap/PixelArthScreenCharTest.h"
	#include "WorldMap/PixelArthScreenCollisionTest.h"
	/*
	#include "PixelArthScreenSimpleActor.h"
	#include "PixelArthScreenMovingActor.h"
	#include "PixelArthScreenIntervals.h"
	#include "PixelArthScreenPhysicsActor.h"
	#include "PixelArthScreenDefFile.h"
	#include "PixelArthScreenLevelFile.h"
	#include "PixelArthScreenConsole.h"
	#include "PixelArthScreenByeBye.h"
	#include "PixelArthScreenRenderLayers.h"
	#include "PixelArthScreenBindingInstructions.h"
	#include "PixelArthScreenLayeredCollisionLevelFile.h"
	#include "PixelArthScreenParticleActors.h"
	#include "PixelArthScreenMessagePassing.h"
	#include "PixelArthScreenMultipleControllers.h"
	#include "PixelArthScreenControllerInstructions.h"
	#include "PixelArthScreenTuningVariables.h"
	#include "PixelArthScreenImageMap.h"
	#include "PixelArthScreenPathfinding.h"
	*/
#endif

//#include "PixelArthScreenMobileSimulator.h"

PixelArthScreen::PixelArthScreen() {}

void PixelArthScreen::Start(){}

void PixelArthScreen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it 
		//  can mess with the pathfinding regeneration.
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if (pa != NULL)
		{
			if (pa->GetBody() != NULL)
			{
				pa->GetBody()->SetUserData(NULL);
				theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
				pa->ResetBody();
			}
		}
		(*it)->Destroy();
		it++;
	}
	_objects.clear();
}

void PixelArthScreen::Update(float dt) {}
void PixelArthScreen::Render() {}



PixelArthGameManager* PixelArthGameManager::s_PixelArthGameManager = NULL;

PixelArthGameManager::PixelArthGameManager()
{	
	//subscribe to messages
	theSwitchboard.SubscribeTo(this, "MoveForwards");
	theSwitchboard.SubscribeTo(this, "MoveBackwards");
	
	#if ANGEL_MOBILE
		//_screens.push_back(new PixelArthScreenMobileSimulator());				// 0
	#else
		_screens.push_back(new PixelArthScreenCharTest());
		_screens.push_back(new PixelArthScreenCollisionTest());
		/*
		_screens.push_back(new PixelArthScreenStart());							// 0
		_screens.push_back(new PixelArthScreenInstructions());					// 1
		_screens.push_back(new PixelArthScreenSimpleActor());					// 2
		_screens.push_back(new PixelArthScreenRenderLayers());					// 3
		_screens.push_back(new PixelArthScreenControllerInstructions());			// 4
		_screens.push_back(new PixelArthScreenMovingActor());					// 5
		_screens.push_back(new PixelArthScreenMultipleControllers());			// 6
		_screens.push_back(new PixelArthScreenMobileSimulator());				// 7
		_screens.push_back(new PixelArthScreenDefFile());						// 8
		_screens.push_back(new PixelArthScreenLevelFile());						// 9
		_screens.push_back(new PixelArthScreenBindingInstructions());			//10
		_screens.push_back(new PixelArthScreenParticleActors());					//11
		_screens.push_back(new PixelArthScreenPhysicsActor());					//12
		_screens.push_back(new PixelArthScreenMessagePassing());					//13
		_screens.push_back(new PixelArthScreenIntervals());						//14
		_screens.push_back(new PixelArthScreenLayeredCollisionLevelFile());		//15
		_screens.push_back(new PixelArthScreenConsole());						//16
		_screens.push_back(new PixelArthScreenTuningVariables());				//17
		_screens.push_back(new PixelArthScreenPathfinding());					//18
		_screens.push_back(new PixelArthScreenImageMap());						//19
		_screens.push_back(new PixelArthScreenByeBye());							//20
		*/
	#endif
	
	unsigned int startingIndex = 0;
	if (_screens.size() > startingIndex)
	{
		theWorld.Add(_screens[startingIndex]);
		_screens[startingIndex]->Start();
		_current = startingIndex;
	}
	else
	{
		_current = -1;
	}
	
	// We must set the sound callback method.  Although, I'm wondering if we should 
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);
	
	sample = theSound.LoadSample("Resources/Sounds/click.ogg", false /*no stream*/);
}

PixelArthGameManager& PixelArthGameManager::GetInstance()
{
	if (s_PixelArthGameManager == NULL)
	{
		s_PixelArthGameManager = new PixelArthGameManager();
	}
	return *s_PixelArthGameManager;
}

PixelArthScreen* PixelArthGameManager::GetCurrentScreen()
{
	return _screens[_current];
}

void PixelArthGameManager::ReceiveMessage(Message* message)
{
	if (message->GetMessageName() == "MoveForwards")
	{
		MoveForwards();
	}
	else if (message->GetMessageName() == "MoveBackwards")
	{
		MoveBackwards();
	}
}

void PixelArthGameManager::MoveForwards()
{
	if ((_current >= 0) && (_current < (int)_screens.size() - 1))
	{
		_screens[_current]->Stop();
		theWorld.Remove(_screens[_current]);
		_screens[++_current]->Start();
		theWorld.Add(_screens[_current]);
		
		if (sample)
			theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
	}
}

void PixelArthGameManager::MoveBackwards()
{
	if (_current > 0)
	{
		_screens[_current]->Stop();
		theWorld.Remove(_screens[_current]);
		_screens[--_current]->Start();
		theWorld.Add(_screens[_current]);
		
		if (sample)
			theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
	}
}

void PixelArthGameManager::Render()
{
	glColor3f(0.5f, 0.5f, 0.5f);
	char* infoString = "";
	int xOffset = 0;
	if (_current == 0)
	{
		infoString = "[A/Space]: Next";
		xOffset = 887;
	}
	else if (_current == _screens.size() - 1)
	{
		infoString = "[Back/Minus]: Previous";
		xOffset = 824;
	}
	else
	{
		infoString = "[A/Space]: Next [Back/Minus]: Previous";
		xOffset = 680;
	}
	DrawGameText(infoString, "ConsoleSmall", xOffset, 563);	//763
}

void PixelArthGameManager::SoundEnded(AngelSoundHandle sound)
{	
	// Detect sounds that have ended here.
}
