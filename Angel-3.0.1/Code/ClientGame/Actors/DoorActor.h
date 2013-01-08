#pragma once
#include "PixelArthGameManager.h"
#include "ButtonActor.h"
#include <vector>

class DoorActor: public PhysicsActor{
public:
	//referenz auf den vector richtig?
	DoorActor(const Vector2& position, const String& spritePath, const std::vector<ButtonActor *>& buttons, bool locked=false);
	void setLocked(const bool locked);
	void addButton( ButtonActor* const);
	inline bool isLocked() const;
	virtual void Update(float dt);

private:
	String m_spritePath;
	bool m_locked;
	std::vector<ButtonActor *> m_buttons;
};