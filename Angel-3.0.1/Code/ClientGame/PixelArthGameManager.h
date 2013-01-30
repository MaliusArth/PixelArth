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

#pragma once
#include <vector>
#include <string>

#include "Physics\CollisionHandler.h"
#include "Physics\Bitmask.h"

// Forward declaration
class CloudActor;
class GroundActor;

class PixelArthScreen : public Renderable, public MessageListener
{
public:
	PixelArthScreen();

	virtual void Start();
	virtual void Stop(); // calls remove on all _objects and deletes them
	virtual void Update(float dt);
	virtual void Render();
	
	virtual void ReceiveMessage(Message *message) {}

    Bitmask * const GetBitmask(const String& path);

protected:
	std::vector<Renderable*> _objects;
	CloudActor *m_sky;
	GroundActor *m_ground;
    Actor *m_arth;

private:
    std::map<String, Bitmask*> m_bitmaskmap;
};

//PixelArthGameManager is a singleton and inherits from:
//  GameManager -- so we receive update and render calls, plus collision notifications
#define thePixelArthGame PixelArthGameManager::GetInstance()

class PixelArthGameManager : public GameManager
{
public:

	void MoveForwards();
	void MoveBackwards();

	static PixelArthGameManager &GetInstance();
	
	PixelArthScreen* GetCurrentScreen();
	
	virtual void Render();

	virtual void SoundEnded(AngelSoundHandle sound);

	virtual void ReceiveMessage(Message* message);

    virtual void Update(float dt);
	
	CollisionHandler *m_collHandler;
protected:
	PixelArthGameManager();
    ~PixelArthGameManager();
	static PixelArthGameManager *s_PixelArthGameManager;

private:
	std::vector<PixelArthScreen*> _screens;
    PixelArthScreen* _mainMenu;
    PixelArthScreen* _gameOver;
	int _current;
	AngelSampleHandle sample;
};