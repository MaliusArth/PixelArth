#include "stdafx.h"
#include "PixelArthGameManager.h"

#if !ANGEL_MOBILE
	#include "WorldMap/PixelArthScreenCharTest.h"
	#include "WorldMap/PixelArthScreenCollisionTest.h"
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
	
	m_collHandler = new CollisionHandler();	
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
