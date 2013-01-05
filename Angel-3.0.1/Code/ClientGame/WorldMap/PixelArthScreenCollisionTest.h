#pragma once

#include "PixelArthGameManager.h"
#include "Actors/GroundActor.h"
//#include "Physics/WorldCollision.h"
#include "Actors/CharActor.h"
#include  "Actors/SnakeActor.h"
#include "Actors/CloudActor.h"

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
	CloudActor *m_background2;
	SnakeActor *m_snake[4];
	Actor *m_hero;
};
