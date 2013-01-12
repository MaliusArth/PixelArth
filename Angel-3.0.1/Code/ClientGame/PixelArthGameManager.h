#pragma once
//#include "stdafx.h"
#include <vector>
#include <string>

#include "Physics\CollisionHandler.h"
#include "Physics\Bitmask.h"
#include "Actors\CharActor.h"

// Forward declarations
//class CharActor;
//class CollisionHandler;
//class Bitmask;

class PixelArthScreen : public Renderable
{
public:
	PixelArthScreen();

	virtual void Start();
	virtual void Stop(); //calls remove on all _objects and deletes them
	virtual void Update(float dt);
	virtual void Render();
	
	virtual void ReceiveMessage(Message *message) {}

    Bitmask * const GetBitmask(const String& path);

    inline CharActor* GetHero(void)
    {
        return m_arth;
    }

protected:
	std::vector<Renderable*> _objects;
    CharActor *m_arth;

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
	int _current;
	AngelSampleHandle sample;
};
