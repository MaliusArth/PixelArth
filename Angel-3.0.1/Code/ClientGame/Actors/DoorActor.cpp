#include "stdafx.h"
#include "DoorActor.h"

DoorActor::DoorActor(const String& spritePath, const Bitmask* const maskOpen, const Bitmask* const maskClosed, const Vector2& position, const Vector2& size, const std::vector<ButtonActor *>& buttons, bool locked)
    : CollidingActor(maskClosed, size)
    , m_spritePath(spritePath)
    , m_buttons(buttons)
    //, m_closed(maskClosed)
    //, m_open(maskOpen)
{
    m_open = new Bitmask(*maskOpen);
    m_open->m_original_mask = maskOpen;
    m_closed = m_mask;
    setLocked(locked);
	SetPosition(position);
    m_open->setSize(size);
    //don't forget to delete the second mask!!! m_mask is deleted by CollidingActor so check which one to delete
    //std::cout << "param:maskOpen: pixelsize: " << maskOpen->getPixelSize().X << " " << maskOpen->getPixelSize().Y << std::endl;
    //std::cout << "param:maskClosed: pixelsize: " << maskClosed->getPixelSize().X << " " << maskClosed->getPixelSize().Y << std::endl;
    //
    //std::cout << "mask: pixelsize: " << m_mask->getPixelSize().X << " " << m_mask->getPixelSize().Y << std::endl;
    //std::cout << "maskClosed: pixelsize: " << m_closed->getPixelSize().X << " " << m_closed->getPixelSize().Y << std::endl;
    //std::cout << "maskOpen: pixelsize: " << m_open->getPixelSize().X << " " << m_open->getPixelSize().Y << std::endl;
    
    SetDensity(1.0f);
	SetFriction(0.0f);
	SetRestitution(0.0f);
	SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();
}
void DoorActor::setLocked(const bool locked){
    //std::cout<<"wall: "<<m_collFlags.wall<<std::endl;
    if((locked) && (m_collFlags.wall==0))
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
	std::vector<ButtonActor*>::iterator it ;
	bool tmp=false;
	for(it=m_buttons.begin();it!=m_buttons.end();it++){
		if(!(*it)->isPressed()){
			tmp=true;
			break;
		}
	}
	setLocked(tmp);

    CollidingActor::Update(dt);
}