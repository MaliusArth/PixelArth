#pragma once

#include "PixelArthGameManager.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
//#include "Actors/CharActor.h"

class Screen4 : public PixelArthScreen
{
public:
	Screen4();
	//~Screen4();

	virtual void Start();
	virtual void Update(float dt);
private:
	TextActor *m_text;
	CloudActor *m_sky;
	GroundActor *m_ground;
    ButtonActor *m_button;
    DoorActor *m_door;
	SnakeActor *m_snake;

	//CharActor *m_arth;
};
