#include "StdAfx.h"
#include "SnakeActor.h"

SnakeActor::SnakeActor(const Bitmask * const mask, const Path& argPath, const Vector2 size, const float argSpeed)
    : CollidingActor(mask, size)
    , m_path(argPath)
    , m_movementSpeed(argSpeed)
{
	SetSprite("Resources/Images/animations/chars/snake/down/snakeDown_00.png");

	//checking if the begin is smaller than the end (correcting if not)
	if(m_path.begin.X > m_path.end.X)
	{
		Vector2 tmp;
		tmp = m_path.begin;
		m_path.begin=m_path.end;
		m_path.end=tmp;
	}
	SetPosition(m_path.begin);
	if(m_path.begin.Y < m_path.end.Y) m_yDir=true;
	else m_yDir=false;
}

void SnakeActor::setFirstPoint(const Vector2& argPoint){
	m_path.begin= argPoint;
}

void SnakeActor::setSecondPoint(const Vector2& argPoint){
	m_path.end= argPoint;
}
void SnakeActor::setMovementSpeed(const float argSpeed){
	m_movementSpeed=argSpeed;
}
//verwende zum überprüfen der position die function MathUtil::FuzzyEquals(Vector2 currPos, Vector2 goalPos)

void SnakeActor::doMovement(bool reverse){
	Vector2 direction;
	direction=m_path.begin-m_path.end;
    if(direction!= Vector2::Zero)
	    direction.Normalize();
	if (reverse)direction= Vector2::Negate(direction);
	//direction= direction*m_movementSpeed;
	float angle_rad = MathUtil::AngleFromVector(direction);
	//bug fix along axes:
	direction.X = direction.X == 0 ? 0 : (m_movementSpeed)*cos(angle_rad);
	direction.Y = direction.Y == 0 ? 0 : ((m_movementSpeed/2))*sin(angle_rad);
    if (GetBody() != NULL)
	    GetBody()->SetLinearVelocity(b2Vec2(direction.X,direction.Y));
}

void SnakeActor::Update(float dt){
    //std::cout << "layer: " << -MathUtil::WorldUnitsToPixels(GetPosition().Y-(GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y) << std::endl;
	//SetLayer(-MathUtil::WorldUnitsToPixels(GetPosition().Y-(GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2));
	
    if (GetPosition().X <= m_path.begin.X)
	{
		
		if(m_yDir==true)
		{
				if(GetPosition().Y <= m_path.begin.Y)
			{

				doMovement(true);
			}
		}
		else 
		{
			if(GetPosition().Y >= m_path.begin.Y)
			{
				doMovement(true);
			}
		}
	}
	if(GetPosition().X >= m_path.end.X)
	{
		if(m_yDir)
		{
			if(GetPosition().Y >= m_path.end.Y)
			{
				doMovement();
			}
		}
		else 
		{
			if(GetPosition().Y <= m_path.end.Y)
			{
				doMovement();
			}
		}
	}
	CollidingActor::Update(dt);
}