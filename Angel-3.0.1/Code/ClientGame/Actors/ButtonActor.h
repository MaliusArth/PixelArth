#pragma once
#include "PixelArthGameManager.h"
class ButtonActor :public PhysicsActor{
public:
	ButtonActor(const Vector2& position, const String& spritePath, bool pressed=false);
	void setPressed(bool pressed=true);
	bool isPressed();
private:
	bool m_pressed;
	String m_path;
	Vector2 position;

};