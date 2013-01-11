#include "stdafx.h"
#include "PixelArthGameManager.h"
#include <map>

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

    m_arth = NULL;

    /*if (m_arth != NULL)
	{
		if (m_arth->GetBody() != NULL)
		{
			m_arth->GetBody()->SetUserData(NULL);
			theWorld.GetPhysicsWorld().DestroyBody(m_arth->GetBody());
			m_arth->ResetBody();
		}
	}
    m_arth->Destroy();*/

    // clear bitmasks
    std::map<String, Bitmask*>::iterator it2 = m_bitmaskmap.begin();
	while(m_bitmaskmap.end() != it2)
	{
        delete (*it2).second;
        //it2 = (*it2).second.erase(it2);
		++it2;
	}
    m_bitmaskmap.clear();
}

void PixelArthScreen::Update(float dt) {

    //for (b2Contact* c = theWorld.GetPhysicsWorld().GetContactList(); c; c = c->GetNext())
    //{
    //    // process c
    //}

    /*std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
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
	_objects.clear();*/

    std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it 
		//  can mess with the pathfinding regeneration.
		CollidingActor* pa = dynamic_cast<CollidingActor*> (*it);
		if (pa != NULL)
		{
            //std::cout << "destroyed? " << pa->IsDestroyed() << std::endl;
            if(!pa->IsDestroyed()){
                std::cout << "SetLayer: " << -MathUtil::WorldUnitsToPixels(pa->GetPosition().Y-(pa->GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2) << std::endl;
                pa->SetLayer(-MathUtil::WorldUnitsToPixels(pa->GetPosition().Y-(pa->GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2));
                // TEST: DEBUG: TODO: WTF
                //pa->SetLayer(10);
                //pa->SetLayer(20);
            }
        }
		it++;
	}

    //std::cout << "pos: " << (m_arth->GetPosition()+(m_arth->GetSize()/2)).X << " bBox: " << m_arth->GetBoundingBox().Max.X << " right: " << MathUtil::GetWorldDimensions().X/2 << std::endl;
    if(m_arth->GetBoundingBox().Max.X >= (MathUtil::GetWorldDimensions().X/2))
    {
        thePixelArthGame.MoveForwards();
	}
    if(m_arth->GetBoundingBox().Min.X <= -(MathUtil::GetWorldDimensions().X/2))
    {
        thePixelArthGame.MoveBackwards();
	}
}
void PixelArthScreen::Render() {}

Bitmask* PixelArthScreen::GetBitmask(const String& path)
{
    if ( m_bitmaskmap.find(path) == m_bitmaskmap.end() ) {
        // not found
        Bitmask* mask = new Bitmask(path);
        m_bitmaskmap.insert(make_pair(path,mask));
    }
    return m_bitmaskmap.at(path);
}



PixelArthGameManager* PixelArthGameManager::s_PixelArthGameManager = NULL;

PixelArthGameManager::PixelArthGameManager()
{	
	//subscribe to messages
	theSwitchboard.SubscribeTo(this, "MoveForwards");
	theSwitchboard.SubscribeTo(this, "MoveBackwards");
	
	m_collHandler = new CollisionHandler();	
	
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
}

PixelArthGameManager::~PixelArthGameManager()
{
    delete m_collHandler;
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
