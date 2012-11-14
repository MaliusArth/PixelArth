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
bool WorldCollision::isCollideing(const Vector2& argBegin,const  Vector2& argEnd) const{
	int i,j;//enum
	
			//const
	for(i= MathUtil::WorldUnitsToPixels(argBegin.X);i < ceil(MathUtil::WorldUnitsToPixels(argEnd.X));i++)
			for(j= MathUtil::WorldUnitsToPixels(argBegin.Y);j <  ceil(MathUtil::WorldUnitsToPixels(argEnd.Y));j++)
				if(m_mask[800*(i+SCREEN_X /2)+(j+SCREEN_Y /2)] == 0) 
				{
					std::cout<<"found collision! X: "<<i<<" Y: "<<j<<std::endl
					<<"Mask coordinates: X: " << i+SCREEN_X /2<< " Y: "<<(j+SCREEN_Y /2)<< std::endl; 
					return true;
				} //end here by collision
	//runs only here when there is no collision*/
	return false;
}

WorldCollision::~WorldCollision(void)
{
	stbi_image_free(m_mask);
	//delete[] m_mask;
}
