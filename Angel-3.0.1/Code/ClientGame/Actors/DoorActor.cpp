#include "stdafx.h"
#include "DoorActor.h"

DoorActor::DoorActor(const Vector2& position, const String& spritePath,const std::vector<ButtonActor *>& buttons, const bool locked):m_spritePath(spritePath), m_buttons(buttons){
	setLocked(locked);
	SetPosition(position);
}
void DoorActor::setLocked(const bool locked){
	if(locked)
	{
		SetSprite(m_spritePath +"off.png");
	}
	else
	{
		SetSprite(m_spritePath +"on.png");
	}
	m_locked=locked;
}
void DoorActor::addButton(ButtonActor* const argButton)
{
	m_buttons.push_back(argButton);
	std::cout<<"penis"<<std::endl;
}
bool DoorActor::isLocked() const
{
	return m_locked;
}
void DoorActor::Update(float dt){
	std::vector<ButtonActor*>::iterator it ;
	bool tmp=false;
	for(it=m_buttons.begin();it!=m_buttons.end();it++){
		if(!(*it)->isPressed()){
			tmp=true;
			break;
		}
	}
	setLocked(tmp);
}