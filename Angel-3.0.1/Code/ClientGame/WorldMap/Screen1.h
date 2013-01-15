#pragma once

#include "PixelArthGameManager.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
#include "Actors\TextActor.h"
//#include "Actors/CharActor.h"

class Screen1 : public PixelArthScreen
{
public:
	Screen1();
	//~Screen1();

	virtual void Start();
	virtual void Update(float dt);
private:
	TextActor *m_text;
	CloudActor *m_sky;
	GroundActor *m_ground;
    CollidingActor *m_propeller;
	//CharActor *m_arth;
};
