#pragma once

#include "PixelArthGameManager.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
//#include "Actors/CharActor.h"

class Screen2 : public PixelArthScreen
{
public:
	Screen2();
	//~Screen2();

	virtual void Start();
	virtual void Update(float dt);
private:
	CloudActor *m_sky;
	GroundActor *m_ground;
	SnakeActor *m_snake[4];

	//CharActor *m_arth;
};
