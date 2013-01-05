#include "PixelArthGameManager.h"


struct Path{
	Vector2 begin, end;
};

class SnakeActor: public PhysicsActor{
public:
	SnakeActor(const Path&, const float& =1.0f);
	void Update(float dt);
private:
	void doMovement(bool reverse=false);
	Path m_path;
	bool m_yDir;
	float m_movementSpeed;
};