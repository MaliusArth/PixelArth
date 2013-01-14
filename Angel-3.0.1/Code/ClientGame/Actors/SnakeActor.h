#pragma once

#include "PixelArthGameManager.h"

struct Path{
	Vector2 begin, end;
};

class SnakeActor : public CollidingActor{
public:
    explicit SnakeActor(const Bitmask * const mask, const Path& argPath, const Vector2 size = 1.0f, const float argSpeed = 1.0f);
	virtual void Update(float dt);
	void setFirstPoint(const Vector2&);
	void setSecondPoint(const Vector2&);
	void setMovementSpeed(const float);
private:

	void doMovement(bool reverse=false);
	Path m_path;
	bool m_yDir;
	float m_movementSpeed;
};