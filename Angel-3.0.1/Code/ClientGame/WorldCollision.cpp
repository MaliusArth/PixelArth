#include "StdAfx.h"
#include "WorldCollision.h"
#include "stb_image.c"

WorldCollision::WorldCollision(const String& arg)
{//tga anschauen
	//stb_image
	int i;
	int x, y, type;
	m_mask = stbi_load(arg.c_str(),&x,&y,&type,0);
	if (m_mask == NULL) std::cout<<"cant inizialise mask"<<std::endl;
	else
	std::cout<<"x:"<<x<<" y:"<<y<<" type:"<<type<<std::endl;
	//m_mask= new char[800*600];
		

}
bool WorldCollision::isCollideing(const Vector& argBegin,const  Vector& argEnd) const{
	int i,j;//enum
			//const
	std::cout<<"collideing function"<<std::endl;
	for(i= argBegin.getX();i < argEnd.getX();i++)
			for(j= argBegin.getY();j < argEnd.getY();j++)
				if(m_mask[800*i+j] == 0) 
				{std::cout<<"found collision "<<i<<" "<<j<<std::endl; return true;} //end here by collision
	//runs only here when there is no collision*/
	return false;
}

WorldCollision::~WorldCollision(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
}
