#include "StdAfx.h"
#include "Physics/Bitmask2.h"
#include "Physics/stb_image.c"
Bitmask2::Bitmask2()
{
	m_mask= NULL;
	m_sizeX= 0;
	m_sizeY= 0;
	m_type= 0;
}
Bitmask2::~Bitmask2()
{
	if(m_mask != NULL)
		delete[] m_mask;
}
//loads a new Bitmask into the memory. 
//If you use that Function the old Bitmask (scaled and not scaled) will be deleted
void Bitmask2::loadMask(const String& path){
	if (m_mask!=NULL)
		delete[] m_mask;
	m_mask = stbi_load(path.c_str(),&m_sizeX,&m_sizeY,&m_type,0);
	if(m_mask == NULL) 
		std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
	if(m_type > 1)
	{
		std::cout<<"please only use 8-bit pictures for bitmasks"<<std::endl;
		exit(1);
	}
}

void Bitmask2::copy(const Bitmask2& argMask, const float& scaleX= 1, const float& scaleY= 1){
	int i, sizeTotal;
	float scale;
	m_sizeX= ceil(argMask.getSizeX()*scaleX);
	m_sizeY= ceil(argMask.getSizeY()*scaleY);
	m_type= argMask.getType();
	sizeTotal= m_sizeX*m_sizeY;
	scale=(argMask.getSizeX()*argMask.getSizeY())/sizeTotal;
	m_mask= new unsigned char[sizeTotal];
	for(i=0;i<sizeTotal;i++)
		m_mask[i]= argMask.getMask()[(int)(i*scale)];
}
int Bitmask2::getSizeX() const{
	return m_sizeX;
}
int Bitmask2::getSizeY() const{
	return m_sizeY;
}
int Bitmask2::getType() const{
	return m_type;
}

unsigned char * Bitmask2::getMask() const{
	return m_mask;
}

unsigned char Bitmask2::getBit(const int& x, const int& y) const{
	if (m_mask!=NULL)
	return m_mask[y*m_sizeX + x];
	return NULL;
}