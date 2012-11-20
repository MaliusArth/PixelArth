#include "StdAfx.h"
#include "WorldCollision.h"
//#include "stb_image.c"

WorldCollision::WorldCollision(const String& arg)
{//tga anschauen
	//stb_image
	m_world = new Bitmask(arg);

	//m_mask = stbi_load(arg.c_str(),&x,&y,&type,0);
	if (m_world == NULL) std::cout<<"cant inizialise mask"<<std::endl;
	else
		std::cout<<"x:"<<m_world->getX()<<" y:"<<m_world->getY()<<" type:"<<m_world->getType()<<std::endl;
	//m_mask= new char[800*600];
		

}
bool WorldCollision::isColliding(const Vector2& argBegin,const  Vector2& argEnd) const{

	int i,j;//enum
	Vector2 begin((int)MathUtil::WorldUnitsToPixels(argBegin.X) +(SCREEN_X/2),(int)MathUtil::WorldUnitsToPixels(argBegin.Y) +(SCREEN_Y/2));
	Vector2 end((int)ceil(MathUtil::WorldUnitsToPixels(argEnd.X)) +(SCREEN_X/2),(int)ceil(MathUtil::WorldUnitsToPixels(argEnd.Y)) +(SCREEN_Y/2));
	if (begin.X < 0 || begin.Y < 0) return true;
	if (end.X > 800 || end.Y > 600) return true;
	std::cout<<"checking "<<begin.X<<", "<<begin.Y<<std::endl;
			//const
	for(i= begin.X; i< end.X; i++)
		for(j= begin.Y; j < end.Y;j++)
			if(m_world->getMask()[800*600-(800*(j+1)-i)] == 0) //mirrored about both axes
				{
					std::cout<<"found collision! X: "<<i<<" Y: "<<j<<std::endl; 
					return true;
				} //end here by collision
	//runs only here when there is no collision*/
	return false;
}


bool WorldCollision::isColliding(const Bitmask& unitMask,const  Vector2& argBegin) const{
		int i,j;//enum
		std::cout<<(float)unitMask.getX()*(30.0f/23.0f)<<std::endl;
	Vector2 begin((int)MathUtil::WorldUnitsToPixels(argBegin.X) + (SCREEN_X/2),
									(int)MathUtil::WorldUnitsToPixels(argBegin.Y) + (SCREEN_Y/2));
	Vector2 end((int)ceil(MathUtil::WorldUnitsToPixels(argBegin.X)+unitMask.getX()*(30.0f/23.0f)) + (SCREEN_X/2),
									(int)ceil(MathUtil::WorldUnitsToPixels(argBegin.Y)+ unitMask.getY()*(30.0f/23.0f)) + (SCREEN_Y/2));
	//MathUtil::WorldUnitsToPixels(argBegin.X)+unitMask.getX()*(30/23)) +(SCREEN_X/2)
	if (begin.X < 0 || begin.Y < 0) return true;
	if (end.X > m_world->getX() || end.Y > m_world->getY()) return true;
	std::cout<<"checking "<<begin.X<<", "<<begin.Y<<std::endl;
			//const
	for(i= begin.X; i< end.X; i++)
		for(j= begin.Y; j < end.Y;j++)
			if(m_world->getMask()[m_world->getX()*m_world->getY() - (m_world->getX()*(j+1)-i)] == 0) //mirrored about both axes
				{

					//if(unitMask.getMask()[unitMask.getX()*unitMask.getY() - (unitMask.getX()*((j+(int)argBegin.Y+1 - (i-(int)argBegin.X) ))) ] == 0)
	//				{
						std::cout<<"found collision! X: "<<i<<" Y: "<<j<<std::endl; 
						return true;
				//	}
				} //end here by collision
	//runs only here when there is no collision*/
	return false;
}
WorldCollision::~WorldCollision(void)
{
	delete[] m_world;
}
