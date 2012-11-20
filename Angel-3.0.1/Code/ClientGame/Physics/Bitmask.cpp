#include "StdAfx.h"
#include "Bitmask.h"
#include "Physics/stb_image.c"
Bitmask::Bitmask(const String& path)
{
	Bitmask::loadMask(path);
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
/*
void Bitmask::setSize(const Vector2& size)
{
	m_size = Vector2(MathUtil::PixelsToWorldUnits((float)m_x)*size.X,MathUtil::PixelsToWorldUnits((float)m_y)*size.Y); 
}
*/
enum CollType Bitmask::checkCollition(const Vector2& begin,const Vector2& end)const{
	int i,j;//enum
	if (begin.X < 0 || begin.Y < 0) return c_wall;
	if (end.X > m_x || end.Y > m_y) return c_wall;
	for(i= begin.X; i< ceil(end.X); i++)
		for(j= begin.Y; j< ceil(end.Y); j++)
			if(m_mask[(m_x*j+i)] == c_wall)
				return c_wall;
	return c_none;
}
unsigned char * Bitmask::getMask() const{
	return m_mask;
}
void Bitmask::loadMask(const String& path){
	m_mask = stbi_load(path.c_str(),&m_x,&m_y,&m_type,0);
	if (m_mask == NULL) std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
	else
	std::cout<<"Bitmask created! x:"<<m_x<<" y:"<<m_y<<" type:"<<m_type<<"inputfile: "<<path<<std::endl;
}

Bitmask::~Bitmask(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
}
