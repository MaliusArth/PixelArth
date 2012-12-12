#include "StdAfx.h"
#include "Physics/Bitmask2.h"
#include "Physics/stb_image.c"
Bitmask2::Bitmask2(const String& path)
{
	m_mask= NULL;
	m_sizeX= 0;
	m_sizeY= 0;
	m_type= 0;
	loadMask(path);
}

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

void Bitmask2::setSize(const Bitmask2& argMask, const float& sizeX, const float& sizeY){
	int i,j;
	float scaleX,scaleY;
	m_sizeX= ceil(MathUtil::WorldUnitsToPixels(sizeX));
	m_sizeY= ceil(MathUtil::WorldUnitsToPixels(sizeY));
	m_type= argMask.getType();
	scaleX=(float)argMask.getSizeX()/(float)m_sizeX;
	scaleY=(float)argMask.getSizeY()/(float)m_sizeY;
	m_mask= new unsigned char[m_sizeX*m_sizeY];
	for(i=0;i<m_sizeX;i++)
	{
		//std::cout<< i<<";"<<(int)((float)i*scaleX)<<std::endl;
		for(j=0;j<m_sizeY;j++)
		{
			
			m_mask[j*m_sizeX+i] =argMask.getBit((int)((float)i*scaleX),(int)((float)j*scaleY));
			/*if(m_mask[i*m_sizeX+j]!=255)
			std::cout<<"X"<<"|";*/
		}
	}
	int debug;
	/*for(debug=0;debug<m_sizeX*m_sizeY; debug++)
		if(m_mask[debug] != 255)
			std::cout<<"X|";*/
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
	return '\n';
}