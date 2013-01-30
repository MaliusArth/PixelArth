#include "stdafx.h"
#include "DoorActor.h"
#include "Actors\ButtonActor.h"

DoorActor::DoorActor(const String& spritePath, const Bitmask* const maskOpen, const Bitmask* const maskClosed, const Vector2& position, const Vector2& size, const std::vector<ButtonActor *>& buttons, bool locked)
    : CollidingActor(maskClosed, size)
    , m_spritePath(spritePath)
    , m_buttons(buttons)
{
    m_open = new Bitmask(*maskOpen);
    m_open->m_original_mask = maskOpen;
    m_closed = m_mask;
    setLocked(locked);

	SetPosition(position);
    m_open->setSize(size);
}
DoorActor::DoorActor(const String& spritePath, const Bitmask* const maskOpen, const Bitmask* const maskClosed, const Vector2& position, const Vector2& size, bool locked)
    : CollidingActor(maskClosed, size)
    , m_spritePath(spritePath)
{
    m_buttons.clear();
    m_open = new Bitmask(*maskOpen);
    m_open->m_original_mask = maskOpen;
    m_closed = m_mask;
    setLocked(locked);

	SetPosition(position);
    m_open->setSize(size);
}
void DoorActor::setLocked(const bool locked)
{
    if((locked) && (m_collFlags.damage==0))
	{
		SetSprite(m_spritePath +"off.png");
        m_mask=m_closed;
	}
	if(!locked)
	{
		SetSprite(m_spritePath +"on.png");
        m_mask=m_open;
	}
	m_locked=locked;
}
void DoorActor::addButton(ButtonActor* const argButton)
{
	m_buttons.push_back(argButton);
}
bool DoorActor::isLocked() const
{
	return m_locked;
}
void DoorActor::Update(float dt){
	std::vector<ButtonActor*>::iterator it;
    if(!m_buttons.empty())
	{
        bool tmp=false;
	    for(it=m_buttons.begin();it!=m_buttons.end();it++){
		    if(!(*it)->isPressed()){
			    tmp=true;
			    break;
		    }
	    }
	    setLocked(tmp);
    }

    CollidingActor::Update(dt);
}