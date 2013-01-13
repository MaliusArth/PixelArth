#pragma once

#include "PixelArthGameManager.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
//#include "Actors/CharActor.h"

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
    ButtonActor *m_button;
    DoorActor *m_door;
	SnakeActor *m_snake[4];

	//CharActor *m_arth;
};
