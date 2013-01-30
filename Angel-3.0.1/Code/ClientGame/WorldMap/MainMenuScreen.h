#pragma once

#include "PixelArthGameManager.h"

class MainMenuScreen : public PixelArthScreen
{
public:
	virtual void Start();
	virtual void Update(float dt);
private:
	CloudActor *m_sky;
	GroundActor *m_ground;
    TextActor *m_text;
    Actor *m_plain;
};
