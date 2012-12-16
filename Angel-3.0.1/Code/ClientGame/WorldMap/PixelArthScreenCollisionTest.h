#pragma once

#include "PixelArthGameManager.h"
#include "Actors/GroundActor.h"
//#include "Physics/WorldCollision.h"
#include "Actors/CharActor.h"

class PixelArthScreenCollisionTest : public PixelArthScreen
{
public:
	PixelArthScreenCollisionTest();
	//~PixelArthScreenCollisionTest();

	virtual void Start();
	virtual void Update(float dt);
private:
	TextActor *m_text;
	GroundActor *m_background;
	Actor *m_hero;
};
