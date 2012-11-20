#include "StdAfx.h"
#include "BitMask.h"
#include "Physics/stb_image.c"
BitMask::BitMask(const String& path)
{
	BitMask::loadMask(path);
}

int BitMask::getX() const{
	return m_x;
}

int BitMask::getY() const{
	return m_y;
}
int BitMask::getType() const{
	return  m_type;
}
unsigned char * BitMask::getMask() const{
	return m_mask;
}
void BitMask::loadMask(const String& path){
	m_mask = stbi_load(path.c_str(),&m_x,&m_y,&m_type,0);
	if (m_mask == NULL) std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
	else
	std::cout<<"BitMask created! x:"<<m_x<<" y:"<<m_y<<" type:"<<m_type<<"inputfile: "<<path<<std::endl;
}

BitMask::~BitMask(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
}
