#include "StdAfx.h"
#include "CloudActor.h"

CloudActor::CloudActor(const String& picturefile, const Vector2& argSpeed)
    : m_speed(argSpeed)
{
	m_repeat=0;
	SetSprite(picturefile, 0, GL_REPEAT, GL_LINEAR, false);
	SetSize(MathUtil::GetWorldDimensions());
	SetColor(1,1,1,1);
	SetUVs(m_repeat,m_repeat+3);
}

void CloudActor::Update(float dt){
	m_repeat.X= m_repeat.X+(m_speed.X*dt);
	m_repeat.Y=m_repeat.Y+(m_speed.Y*dt);
	if(m_repeat.X>4.0f) m_repeat.X=0;
	if(m_repeat.Y>4.0f) m_repeat.Y=0;
	SetUVs(m_repeat,m_repeat+3);
}