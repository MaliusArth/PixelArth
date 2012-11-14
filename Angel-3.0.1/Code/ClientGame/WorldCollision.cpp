#include "StdAfx.h"
#include "WorldCollision.h"
#include "stb_image.c"

WorldCollision::WorldCollision(const String& arg)
{//tga anschauen
	//stb_image
	int i;
	int x=800, y=600, type=1;
	m_mask = stbi_load(arg.c_str(),&x,&y,&type,0);
	if (m_mask == NULL) std::cout<<"cant inizialise mask"<<std::endl;
	else
	std::cout<<"x:"<<x<<" y:"<<y<<" type:"<<type<<std::endl<<"array: "<<sizeof(m_mask)<<std::endl;
	//m_mask= new char[800*600];
		

}
bool WorldCollision::isCollideing(const Vector2& argBegin,const  Vector2& argEnd) const{
	int i,j;//enum
	Vector2 begin(MathUtil::WorldUnitsToPixels(argBegin.X) +(SCREEN_X/2),MathUtil::WorldUnitsToPixels(argBegin.Y) +(SCREEN_Y/2));
	Vector2 end(ceil(MathUtil::WorldUnitsToPixels(argEnd.X)) +(SCREEN_X/2),ceil(MathUtil::WorldUnitsToPixels(argEnd.Y)) +(SCREEN_Y/2));
	std::cout<<"checking "<<begin.X<<", "<<begin.Y<<std::endl;
			//const
	for(i= begin.X; i< end.X; i++)
		for(j= begin.Y; j < end.Y;j++)
				if(m_mask[800*600-(800*(j+1)-i)] == 0) //mirrored about both axes
				{
					std::cout<<"found collision! X: "<<i<<" Y: "<<j<<std::endl; 
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
