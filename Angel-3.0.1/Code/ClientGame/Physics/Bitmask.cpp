#include "StdAfx.h"
#include "Bitmask.h"
#include "Physics/stb_image.c"

#include <iostream>
#include <fstream>

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
	loadMask(m_path);
    m_original_mask = nullptr;
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

Bitmask::Bitmask(const String& path, Bitmask * const original)
	: m_path(path)
{
	loadMask(m_path);
    m_original_mask = original;
};

Bitmask::~Bitmask(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
};

/// <summary>Loads bitmask from file
/// <para>Sets m_size and m_type</para></summary>
/// <param name="path">Path to the bitmask file</param>
void Bitmask::loadMask(const String& path)
{
    m_mask = stbi_load(path.c_str(),&m_size.X,&m_size.Y,&m_type,1);
	if (m_mask == NULL) std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
	else
	std::cout << "Bitmask created! x: " << m_size.X << " y: " << m_size.Y << " type: " << m_type << " inputfile: " << path << std::endl;
};

String Bitmask::getPath(void) const
{
	return m_path;
};

void Bitmask::setSize(const float& sizeX, const float& sizeY){
    Bitmask* maskToScale = m_original_mask != nullptr ? m_original_mask : this;
    
    // check if this bitmask isn't the same as the one in the hashmap
    int i,j;
	float scaleX,scaleY;
	m_size.X= ceil(MathUtil::WorldUnitsToPixels(sizeX));
	m_size.Y= ceil(MathUtil::WorldUnitsToPixels(sizeY));
	//m_type= argMask.getType();
	scaleX=(float)maskToScale->getPixelSize().X/(float)m_size.X;
	scaleY=(float)maskToScale->getPixelSize().Y/(float)m_size.Y;
	m_mask= new unsigned char[m_size.X*m_size.Y];
	for(i=0;i<m_size.X;i++)
	{
		//std::cout<< i<<";"<<(int)((float)i*scaleX)<<std::endl;
		for(j=0;j<m_size.Y;j++)
		{
			
			m_mask[j*m_size.X+i] = maskToScale->getBit((int)((float)i*scaleX),(int)((float)j*scaleY));
			//if(m_mask[i*m_sizeX+j]!=255)
			//std::cout<<"X"<<"|";
		}
	}

	using namespace std;
		//int i, j;
		std::ofstream myfile;
		myfile.open ("mask.txt", ios::app);
		//std::cout<<"size: "<<getPixelSize().X<<std::endl;
		for(i= 0;i<getPixelSize().Y;i++)
		{
			//myfile << i << ". ";
			for(j=0;j<getPixelSize().X;j++)
			{

				//std::cout<<(int)getBit(j,i)<<"|";
				if(getBit(j,i) != 255) myfile<<"X";//<<std::endl;
				else if(getBit(j,i) != 0)  myfile<<" ";
				else myfile<<"f";
			}
			myfile<<"\n";
		}
	//int debug;
	//for(debug=0;debug<m_sizeX*m_sizeY; debug++)
	//    if(m_mask[debug] != 255)
	//	    std::cout<<"X|";
};

void Bitmask::setSize(const Vector2& size){
    Bitmask::setSize(size.X, size.Y);
};

unsigned char Bitmask::getBit(const int& xPos, const int& yPos) const
{
    if (m_mask!=NULL)
        return m_mask[yPos*m_size.X + xPos];
	return '\n';
};

unsigned char Bitmask::getBit(const Vec2i& pos) const
{
    return Bitmask::getBit(pos.X, pos.Y);
};