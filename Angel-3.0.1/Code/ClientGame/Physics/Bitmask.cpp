#include "StdAfx.h"
#include "Physics/Bitmask.h"
#include "Physics/stb_image.c"

Bitmask::Bitmask(const String& path)
{
	Bitmask::loadMask(path);
}

float Bitmask::center(const float& arg) const{
	return floor(arg+0.5);
}
int Bitmask::getX() const{
	return m_x;
}

int Bitmask::getY() const{
	return m_y;
}

int Bitmask::getType() const{
	return  m_type;
}

Vector2 Bitmask::getScale() const{
	return m_scale;
}

float Bitmask::getScaleX() const{
	return getScale().X;
}
	float Bitmask::getScaleY() const{
		return getScale().Y;
	}

enum CollType Bitmask::checkCollition(const Vector2& begin,const Vector2& end)const{
	int i,j;//enum
	if (begin.X < 0 || begin.Y < 0) return c_wall;
	if (end.X > m_x || end.Y > m_y) return c_wall;
	for(i= begin.X; i< ceil(end.X); i++)
		for(j= begin.Y; j< ceil(end.Y); j++)
			if(m_mask[(m_x*j+i)] != c_none)
				return c_wall;
	return c_none;
}

std::list<Collision> Bitmask::getAllCollisions(const Vector2& argBegin, const Vector2& argEnd) const{
	Vector2 begin, end;
	std::list<Collision> collList;
	int i, j;
	CollType current;
	begin.X =argBegin.X/m_scale.X;
	begin.Y =argBegin.Y/m_scale.Y;
	end.X =argEnd.X/m_scale.X;
	end.Y =argEnd.Y/m_scale.Y;
	//current= m_mask[((int)(begin.Y+0.5))*m_x+((int) (begin.X +  0.5))];
	//checking first pixel
	if(m_mask[((int)center(begin.Y))*m_x+((int) center(begin.X))] != c_none)
	{
		current=c_wall;
		collList.push_front(Collision(Vector2(begin.X,begin.Y),Vector2(center(begin.Y)+0.5,center(begin.Y)+0.5),current));
	}

	//first line, last pixel
	if(m_mask[((int)center(begin.Y))*m_x+((int) center(end.X))] != c_none)
	{
		current=c_wall;
		collList.push_front(Collision(Vector2(center(end.X)-0.5,begin.Y),Vector2(end.X,center(begin.Y)+0.5),current));
	}
	//last line, first pixel
	if(m_mask[((int)center(end.Y))*m_x+((int) center(begin.X))] != c_none)
	{
		current=c_wall;
		collList.push_front(Collision(Vector2(begin.X,center(end.Y)-0.5),Vector2(center(begin.X)+0.5,end.Y),current));
	}
	//last line, last pixel
	if(m_mask[((int)center(end.Y))*m_x+((int) center(end.X))] != c_none)
	{
		current=c_wall;
		collList.push_front(Collision(Vector2(center(end.X)-0.5,center(end.Y)-0.5),Vector2(end.X,end.Y),current));
	}
	for(i=center(begin.X)+1;i<=center(end.X)-1;i++)
	{
		if(m_mask[((int)center(begin.Y))*(int)(m_x)+i] != c_none)
		{
			current= c_wall;
			collList.push_front(Collision(Vector2(i-0.5,begin.Y),Vector2(i+0.5,center(begin.Y)+0.5),current));
		}
		if(m_mask[((int)center(end.Y))*(int)(m_x)+i] != c_none)
		{
			current= c_wall;
			collList.push_front(Collision(Vector2(i-0.5,center(end.Y)-0.5),Vector2(i+0.5,end.Y),current));
		}
	}
	for(i=center(begin.Y)+1;i<=center(end.Y)-1;i++)
	{
		if(m_mask[((int)center(begin.Y))*m_x+(int)center(begin.X)] != c_none)
		{
			current= c_wall;
			collList.push_front(Collision(Vector2(begin.X,i-0.5),Vector2(center(begin.X)+0.5,i+0.5),current));
		}
		if(m_mask[((int)center(end.Y))*m_x+(int)center(end.X)] != c_none)
		{
			current= c_wall;
			collList.push_front(Collision(Vector2(center(end.X)-0.5,i-0.5),Vector2(end.X,i+0.5),current));
		}
	}

	for(i=center(begin.Y)+1;i<=center(end.Y)-1;i++)
		for(j=center(begin.X)+1;j<=center(end.X)-1;j++)
		{
			if(m_mask[i*m_x+j] != c_none)
			{
				current= c_wall;
				collList.push_front(Collision(Vector2(i-0.5,j-0.5),Vector2(i+0.5,j+0.5),current));
			}
		}
	return collList;
}

std::list<CollType> Bitmask::getAllCollisionTypes(const Vector2& argBegin, const Vector2& argEnd) const{
	int i, j;
	CollType current;
	std::list<CollType> collTypeList;
	Vector2 begin, end;
	begin.X =argBegin.X/m_scale.X;
	begin.Y =argBegin.Y/m_scale.Y;
	end.X =argEnd.X/m_scale.X;
	end.Y =argEnd.Y/m_scale.Y;
	for(i=center(begin.X);i<=center(end.X);i++)
		for(j=center(begin.Y);j<=center(end.Y);j++)
		{
			if(m_mask[j*m_x+i] != c_none)
			{
				current= c_wall;
				collTypeList.push_front( CollType(current));
			}
		}
		return collTypeList;
}

void Bitmask::setScale(const Vector2& size){
	m_scale = size;
}

void Bitmask::setScaleX(const float& scaleX){
	m_scale.X=scaleX;
}

void Bitmask::setScaleY(const float& scaleY){
	m_scale.Y=scaleY;
}

void Bitmask::setSizeInWorldUnits(const Vector2& size){
	setSizeXInWorldUnits(size.X);
	setSizeYInWorldUnits(size.Y);
}
void Bitmask::setSizeXInWorldUnits(const float& size){
	m_scale.X = MathUtil::WorldUnitsToPixels(size)/m_x;
}
void Bitmask::setSizeYInWorldUnits(const float& size){
	m_scale.Y = MathUtil::WorldUnitsToPixels(size)/m_y;
}
unsigned char * Bitmask::getMask() const{
	return m_mask;
}
void Bitmask::loadMask(const String& path){
	m_mask = stbi_load(path.c_str(),&m_x,&m_y,&m_type,0);
	if (m_mask == NULL) std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
}

Bitmask::~Bitmask(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
}
