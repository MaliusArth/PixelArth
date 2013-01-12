#pragma once

#include "PixelArthGameManager.h"

//#include "Actors/CharActor.h"


class PixelArthScreenCharTest : public PixelArthScreen
{
public:
	PixelArthScreenCharTest();
	//~PixelArthScreenCharTest();
	
	virtual void Start();
	virtual void Update(float dt);

private:
	TextActor *t;
	//CharActor *m_arth;
};
