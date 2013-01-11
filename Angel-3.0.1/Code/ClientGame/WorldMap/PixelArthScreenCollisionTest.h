#pragma once

//#include "PixelArthGameManager.h"
#include "Actors/GroundActor.h"
//#include "Physics/WorldCollision.h"
#include "Actors/CharActor.h"
#include "Actors/SnakeActor.h"
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
	CloudActor *m_sky;
	GroundActor *m_ground;
	SnakeActor *m_snake[4];

	//CharActor *m_arth;
};
