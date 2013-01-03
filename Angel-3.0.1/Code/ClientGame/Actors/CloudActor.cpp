#include "StdAfx.h"
#include "CloudActor.h"


CloudActor::CloudActor(const String& picturefile)
{
	m_repeat=0;
	SetSprite(picturefile, 0, GL_REPEAT, GL_LINEAR, false);
	SetSize(MathUtil::PixelsToWorldUnits(800),MathUtil::PixelsToWorldUnits(600));
	SetColor(1,1,1,1);
	SetUVs(m_repeat,m_repeat+3);
	SetLayer(-2);
	
	//this->set
}

void CloudActor::Update(float dt){
	m_repeat.X= m_repeat.X+(0.05f*dt);
	m_repeat.Y=m_repeat.Y+(0.0f*dt);
	if(m_repeat.X>4.0f) m_repeat.X=0;
	if(m_repeat.Y>4.0f) m_repeat.Y=0;
	SetUVs(m_repeat,m_repeat+3);
}
//void GroundActor::Render(){
//}
/*
CloudActor::~CloudActor(void)
{
}
*/