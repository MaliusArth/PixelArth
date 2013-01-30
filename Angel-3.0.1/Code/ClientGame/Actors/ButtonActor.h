#pragma once
#include "PixelArthGameManager.h"
#include "CollidingActor.h"
class ButtonActor : public CollidingActor{
public:
	ButtonActor(const String& spritePath, const Bitmask * const mask, const Vector2& position = 0.0f, const Vector2& size = 1.0f, float pressed=-1.0f);
	void setPressed(bool pressed=true);
	bool isPressed();
	virtual void Update(float dt);
	virtual void Collide(const CollFlags& collFlags);
    void setTimer(float);
	float getTimer();

private:
	bool m_pressed;
	float m_time, m_countup;
	String m_path;
	Vector2 position;
};