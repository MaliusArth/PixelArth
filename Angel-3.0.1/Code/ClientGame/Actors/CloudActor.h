#pragma once
#include "Actors/Actor.h"

class CloudActor : public Actor
{
public:
	CloudActor(const String&);
	virtual void Update(float dt);
	//virtual void Render();
	//~CloudActor(void);
private:
	Vector2 m_repeat;
};
