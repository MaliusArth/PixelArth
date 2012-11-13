#include "StdAfx.h"
#include "WorldCollision.h"


WorldCollision::WorldCollision(const String& arg)
{//tga anschauen
	//stb_image
	int i;
	std::ifstream maskfile;
	m_mask= new char[800*600];
	maskfile.open(arg);
	if(maskfile.is_open()){
		for (i=0; i<6;i++){
			maskfile.getline(m_mask+i,600);
		}
	}
		

}
bool WorldCollision::isCollideing(const Vector& argBegin,const  Vector& argEnd) const{
	int i,j;//enum
			//const
	for(i= argBegin.getX();i < argEnd.getX();i++)
			for(j= argBegin.getY();j < argEnd.getY();j++)
				if(m_mask[800*i+600] != 0) 
					return true; //end here by collision
	//runs only here when there is no collision
	return false;
}

WorldCollision::~WorldCollision(void)
{
	delete[] m_mask;
}
