#include "StdAfx.h"
#include "Bitmask.h"
#include "Physics/stb_image.c"

//enum BitField
//{
//	NONE	= 1 << 0,
//	RUNNING	= 1 << 1,
//	JUMPING	= 1 << 2,
//};
//
//template <typename T>
//class Flags
//{
//	/*void set(T val)
//	{
//		m_bits = val;
//	}*/
//private:
//uint32 m_bits;
//};

Bitmask::Bitmask(const String& path)
	: m_path(path)
{
	Bitmask::loadMask(m_path);
	/*
	//TEST
	int state = NONE;
	//state = 2;
	//flags adden
	state |= RUNNING;

	//flags removen
	state &= ~(JUMPING);


	//player::React(Flags<BitField>);
	*/
};

Bitmask::~Bitmask(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
};

void Bitmask::loadMask(const String& path)
{
    m_mask = stbi_load(path.c_str(),&m_size.X,&m_size.Y,&m_type,0);
	if (m_mask == NULL) std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
	else
	std::cout << "Bitmask created! x: " << m_size.X << " y: " << m_size.Y << " type: " << m_type << " inputfile: " << path << std::endl;
};

//String Bitmask::getPath(void) const
//{
//	return m_path;
//};

void Bitmask::setSize(const float& x, const float& y){
    //TODO
};

void Bitmask::setSize(const Vector2& size){
    //TODO
};

unsigned char Bitmask::getBit(const int& xPos, const int& yPos) const
{
    if (m_mask!=NULL)
        return m_mask[yPos*m_size.X + xPos];
	return '\n';
};
