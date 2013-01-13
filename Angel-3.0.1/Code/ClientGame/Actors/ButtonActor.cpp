#include "stdafx.h"
#include "ButtonActor.h"

ButtonActor::ButtonActor(const String& spritePath, const Bitmask * const mask, const Vector2& position, const Vector2& size, float timer)
    : CollidingActor(mask, size)
    , m_path(spritePath)
    , m_time(timer)
{
	setPressed(false);

	SetPosition(position);
	SetDensity(1.0f);
	SetFriction(0.0f);
	SetRestitution(0.0f);
	SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();
}

void ButtonActor::setTimer(float timer)
{
	m_time=timer;
}

float ButtonActor::getTimer()
{
	return m_time;
}

void ButtonActor::setPressed(bool pressed){
	ClearSpriteInfo();
	if(pressed)
	{
		SetSprite(m_path +"on.png");
		m_countup=0;
	}
	else
		SetSprite(m_path +"off.png");
	m_pressed=pressed;
	
}

bool ButtonActor::isPressed(){
	return m_pressed;
}

void ButtonActor::Update(float dt){
	if(m_time>0 && m_pressed==true)
	{
		m_countup+= dt;
		std::cout<<m_countup<<std::endl;
		if(m_countup>=m_time)
			setPressed(false);

	}
    CollidingActor::Update(dt);
}

void ButtonActor::Collide(const CollFlags& collFlags)
{
    if(m_collFlags.wall)
    {
        setPressed(true);
    }
    CollidingActor::Collide(collFlags);
}