#pragma once
#include<math.h>
enum CollType{
	c_wall =0,
	c_floor =255
};
class Collision{
private:
	Vector2 m_begin, m_end;
	CollType m_type;
public:
	Collision(const Vector2&, const Vector2&, const CollType&);
	Vector2 getBegin() const;
	Vector2 getEnd() const;
	CollType getType() const;
	//~Collision();
};