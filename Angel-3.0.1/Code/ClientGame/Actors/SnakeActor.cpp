#include "StdAfx.h"
#include "SnakeActor.h"


SnakeActor::SnakeActor(const Path& argPath, const float& argSpeed):m_path(argPath), m_movementSpeed(argSpeed){
	//checking if the begin is smaller than the end (correcting if not)
	if(m_path.begin.X > m_path.end.X)
	{
		Vector2 tmp;
		tmp = m_path.begin;
		m_path.begin=m_path.end;
		m_path.end=tmp;
	}
	this->SetPosition(m_path.begin);
	if(m_path.begin.Y < m_path.end.Y) m_yDir=true;
	else m_yDir=false;
	SetDensity(1.0f);
	SetFriction(0.0f);
	SetColor(0,0,0); 
	SetRestitution(0.0f);
	SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();
	doMovement();

	
}

//verwende zum überprüfen der position die function MathUtil::FuzzyEquals(Vector2 currPos, Vector2 goalPos)

void SnakeActor::doMovement(bool reverse){
	Vector2 direction;
	direction=m_path.begin-m_path.end;
	direction.Normalize();
	if (reverse)direction= Vector2::Negate(direction);
	//direction= direction*m_movementSpeed;
	float angle_rad = MathUtil::AngleFromVector(direction);
	//bug fix along axes:
	direction.X = direction.X == 0 ? 0 : (m_movementSpeed)*cos(angle_rad);
	direction.Y = direction.Y == 0 ? 0 : ((m_movementSpeed/2))*sin(angle_rad);
	GetBody()->SetLinearVelocity(b2Vec2(direction.X,direction.Y));
}
void SnakeActor::Update(float dt){
	PhysicsActor::Update(dt);
	SetLayer(-MathUtil::WorldUnitsToPixels(GetPosition().Y-(GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y));
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
}