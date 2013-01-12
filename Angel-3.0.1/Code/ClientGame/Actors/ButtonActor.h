#pragma once
#include "PixelArthGameManager.h"
class ButtonActor :public PhysicsActor{
public:
	ButtonActor(const Vector2& position, const String& spritePath, float pressed=-1.0f);
	void setPressed(bool pressed=true);
	bool isPressed();
	virtual void Update(float dt);
	void setTimer(float);
	float getTimer();
private:
	bool m_pressed;
	float m_time, m_countup;
	String m_path;
	Vector2 position;

};