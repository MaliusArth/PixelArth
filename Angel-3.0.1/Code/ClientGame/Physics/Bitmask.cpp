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
