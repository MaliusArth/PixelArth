#include "stdafx.h"
#include "ButtonActor.h"

ButtonActor::ButtonActor(const Vector2& position, const String& spritePath, bool pressed):m_path(spritePath){
	setPressed(pressed);
	//SetSize(MathUtil::GetWorldDimensions());
	SetColor(1,1,1,1);
	SetPosition(position);
	SetDensity(1.0f);
	SetFriction(0.0f);
	SetRestitution(0.0f);
	SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();
}

void ButtonActor::setPressed(bool pressed){
	ClearSpriteInfo();
	if(pressed)
		SetSprite(m_path +"on.png");
	else
		SetSprite(m_path +"off.png");
	m_pressed=pressed;
	
}
	bool ButtonActor::isPressed(){
		return m_pressed;
	}