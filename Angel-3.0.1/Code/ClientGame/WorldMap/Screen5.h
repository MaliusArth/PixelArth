#pragma once

#include "PixelArthGameManager.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
//#include "Actors/CharActor.h"

class Screen5 : public PixelArthScreen
{
public:
	Screen5();
	//~Screen5();

	virtual void Start();
	virtual void Update(float dt);
private:
	//TextActor *m_text;
	CloudActor *m_sky;
	GroundActor *m_ground;
    TextActor *m_text;
    Actor *m_plain;
	//CharActor *m_arth;
};
