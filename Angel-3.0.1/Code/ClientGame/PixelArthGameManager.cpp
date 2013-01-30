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

//
// This file contains class definitions for both PixelArthScreen and PixelArthGameManager
//

#include "stdafx.h"
#include "PixelArthGameManager.h"
#include <map>

#include "WorldMap/Screen1.h"
#include "WorldMap/Screen2.h"
#include "WorldMap/Screen3.h"
#include "WorldMap/Screen4.h"
#include "WorldMap/Screen5.h"
#include "WorldMap/GameOverScreen.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\CharActor.h"

PixelArthScreen::PixelArthScreen()
    : m_sky(NULL)
    , m_ground(NULL)
    , m_arth(NULL)
{}

void PixelArthScreen::Start()
{
    if(m_sky != NULL)
    theWorld.Add(m_sky, "Sky");
    if(m_ground !=NULL)
    theWorld.Add(m_ground, "Ground");
    if(m_arth != NULL)
    theWorld.Add(m_arth, "Front");
    
    if(m_sky != NULL)
    _objects.push_back(m_sky);
    if(m_ground !=NULL)
    _objects.push_back(m_ground);
    if(m_arth != NULL)
    _objects.push_back(m_arth);

    std::vector<Renderable*>::iterator it = _objects.begin();
    while(_objects.end() != it)
    {
        PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
        if (pa != NULL)
        {
            pa->InitPhysics();
        }
        it++;
    }
}

void PixelArthScreen::Stop()
{
    std::vector<Renderable*>::iterator it = _objects.begin();
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
        //delete (*it);
        it++;
    }
    _objects.clear();

    m_arth = nullptr;
    m_ground = nullptr;
    m_sky = nullptr;

    // clear bitmasks
    std::map<String, Bitmask*>::iterator it2 = m_bitmaskmap.begin();
    while(m_bitmaskmap.end() != it2)
    {
        delete (*it2).second;
        ++it2;
    }
    m_bitmaskmap.clear();
}

void PixelArthScreen::Update(float dt)
{
    std::vector<Renderable*>::iterator it = _objects.begin();
    while(_objects.end() != it)
    {
        CollidingActor* pa = dynamic_cast<CollidingActor*> (*it);

        if (pa != NULL)
        {
            if(pa->IsLayered())
            {
                if(!pa->IsDestroyed()){
                    pa->SetLayer(-MathUtil::WorldUnitsToPixels(pa->GetPosition().Y-(pa->GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2));
                }
            }
        }
        it++;
    }
    CharActor* arth = dynamic_cast<CharActor*>(m_arth);
    if(arth != nullptr)
    {
        if(!arth->IsDead())
        {
            if(arth->GetBoundingBox().Max.X >= (MathUtil::GetWorldDimensions().X/2))
            {
                theSwitchboard.Broadcast(new Message("MoveForwards"));
            }
            else if(arth->GetBoundingBox().Min.X <= -(MathUtil::GetWorldDimensions().X/2))
            {
                theSwitchboard.Broadcast(new Message("MoveBackwards"));
            }
        }
    }

    if(theInput.IsKeyDown('q'))
    {
        theSwitchboard.Broadcast(new Message("Dead"));
    }
}

void PixelArthScreen::Render() {}

Bitmask * const PixelArthScreen::GetBitmask(const String& path)
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
    theSwitchboard.SubscribeTo(this, "Dead");
    theSwitchboard.SubscribeTo(this, "Retry");
	
    m_collHandler = new CollisionHandler();	
	
    _screens.push_back(new Screen1());
    _screens.push_back(new Screen2());
    _screens.push_back(new Screen3());
    _screens.push_back(new Screen4());
    _screens.push_back(new Screen5());
    _gameOver = new GameOverScreen();
    
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
	
    //sample = theSound.LoadSample("Resources/Sounds/click.ogg", false /*no stream*/);
}

PixelArthGameManager::~PixelArthGameManager()
{
    GameManager::~GameManager();
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

void PixelArthGameManager::Update(float dt)
{
    GameManager::Update(dt);

    b2Contact* contactlist = theWorld.GetPhysicsWorld().GetContactList();
    
    while(contactlist != NULL)
    {
        if((contactlist->GetFixtureA()->GetBody()->GetUserData() == contactlist->GetFixtureB()->GetBody()->GetUserData()))
        {
            //std::cout << "WTF " << (contactlist->GetFixtureA()->GetBody()->GetUserData()) << std::endl;
        }
        if(!(contactlist->GetFixtureA()->GetBody()->GetUserData() == contactlist->GetFixtureB()->GetBody()->GetUserData()))
        {
            PhysicsActor *pa = static_cast<PhysicsActor*>(contactlist->GetFixtureA()->GetBody()->GetUserData());
            CollidingActor *ca = dynamic_cast<CollidingActor*>(pa);

            if(ca != NULL)
            {
                PhysicsActor *pb = static_cast<PhysicsActor*>(contactlist->GetFixtureB()->GetBody()->GetUserData());
                CollidingActor *cb = dynamic_cast<CollidingActor*>(pb);

                if (ca != NULL && cb != NULL)
                {
                    CollFlags cf;

                    cf = m_collHandler->checkCollisions(ca->GetPosition(), *(ca->GetMask()), cb->GetPosition(), *(cb->GetMask()));
                    
                    ca->Collide(cf);

                    cf = m_collHandler->checkCollisions(cb->GetPosition(), *(cb->GetMask()), ca->GetPosition(), *(ca->GetMask()));
                    cb->Collide(cf);
                }
            }
        }
        contactlist = contactlist->GetNext();
    }
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
    else if (message->GetMessageName() == "Dead")
    {
        _screens[_current]->Stop();
        theWorld.Remove(_screens[_current]);

        //_screens[_current]->Start();
        //theWorld.Add(_screens[_current]);

        //TODO: GameOverScreen
        _gameOver->Start();
        theWorld.Add(_gameOver);
    }
    else if (message->GetMessageName() == "Retry")
    {
        _gameOver->Stop();
        theWorld.Remove(_gameOver);

        //TODO: GameOverScreen
        _screens[_current]->Start();
        theWorld.Add(_screens[_current]);
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
		
        //if (sample)
        //    theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
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
		
        //if (sample)
        //    theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
    }
}

void PixelArthGameManager::Render()
{
}

void PixelArthGameManager::SoundEnded(AngelSoundHandle sound)
{	
    // Detect sounds that have ended here.
}