#pragma once

#include "stdafx.h"
#include <vector>
#include <string>

#include "Physics\CollisionHandler.h"

class PixelArthScreen : public Renderable
{
public:
	PixelArthScreen();

	virtual void Start();
	virtual void Stop(); //calls remove on all _objects and deletes them
	virtual void Update(float dt);
	virtual void Render();
	
	virtual void ReceiveMessage(Message *message) {}

    Bitmask* GetBitmask(const String& path);

protected:
	std::vector<Renderable*> _objects;
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
	
	CollisionHandler *m_collHandler;
protected:
	PixelArthGameManager();
	static PixelArthGameManager *s_PixelArthGameManager;

private:
	std::vector<PixelArthScreen*> _screens;
	int _current;
	AngelSampleHandle sample;
};
