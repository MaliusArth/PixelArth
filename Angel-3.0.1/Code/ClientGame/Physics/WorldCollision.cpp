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
		float scaleX, scaleY;
		scaleX=scaleY=30.0f/23.0f;
	Vector2 begin((int)MathUtil::WorldUnitsToPixels(argBegin.X) + (SCREEN_X/2),
		(int)(m_world->getY()-(MathUtil::WorldUnitsToPixels(argBegin.Y)+ unitMask.getY()*scaleY + (SCREEN_Y/2))));
	Vector2 end((int)ceil(MathUtil::WorldUnitsToPixels(argBegin.X)+unitMask.getX()*scaleX + (SCREEN_X/2)),
									(int)ceil(m_world->getY()-(MathUtil::WorldUnitsToPixels(argBegin.Y) + (SCREEN_Y/2))));
	if (begin.X < 0 || begin.Y < 0) return c_wall;
	if (end.X > m_world->getX() || end.Y > m_world->getY()) return c_wall;
	for(i= begin.X; i< ceil(end.X); i++)
 		for(j= begin.Y; j< ceil(end.Y); j++)
			if(m_world->getMask()[(m_world->getX()*j+i)] == c_wall){
				if(unitMask.checkCollition(Vector2((i-begin.X)/scaleX,(j-begin.Y)/scaleY),Vector2((i-begin.X)/scaleX,(j-begin.Y)/scaleY)) != c_none) return true;
			}
	return false;
}
WorldCollision::~WorldCollision(void)
{
	delete[] m_world;
}
