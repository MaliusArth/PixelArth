#pragma once
#include "PixelArthGameManager.h"
#include "ButtonActor.h"
#include "CollidingActor.h"
#include <vector>

class DoorActor: public CollidingActor{
public:
	//referenz auf den vector richtig?
	DoorActor(const String& spritePath, const Bitmask* const maskon, const Bitmask* const maskoff, const Vector2& position, const Vector2& size, const std::vector<ButtonActor *>& buttons, bool locked=false);
	void setLocked(const bool locked);
	void addButton( ButtonActor* const);
	inline bool isLocked() const;
	virtual void Update(float dt);

private:
	String m_spritePath;
	bool m_locked;
    Bitmask* m_closed, *m_open;
	std::vector<ButtonActor *> m_buttons;
};