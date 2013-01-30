#pragma once
//#include "Actors/Actor.h"

class CloudActor : public Actor
{
public:
	CloudActor(const String&, const Vector2& argSpeed = Vector2(0.04f,0.015f));
	virtual void Update(float dt);
private:
	Vector2 m_repeat, m_speed;
};