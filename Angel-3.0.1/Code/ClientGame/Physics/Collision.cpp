#include "stdafx.h"
#include "Physics\Collision.h"

Collision::Collision(const Vector2& begin, const Vector2& end, const CollType& type) : m_begin(begin),m_end(end),m_type(type){}
Vector2 Collision::getBegin() const{
	return m_begin;
}
Vector2 Collision::getEnd() const{
	return m_end;
}
CollType Collision::getType() const{
	return m_type;
}