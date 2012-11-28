#include "StdAfx.h"
#include "CollisionChecker.h"

std::list<CollType> CollisionChecker::checkCollisions(const Vector2& argBegin1,const Bitmask& bitmask1, const Vector2& argBegin2, const Bitmask& bitmask2) const{
	//converting to bitmask coordinates
	int i;
	Vector2 begin1, end1, begin2, end2, interBegin, interEnd;
	bool foundTypes[256];
	std::list<Collision> collList;
	std::list<Collision>::iterator it;
	std::list<CollType> collTypeList;
	std::list<CollType>::iterator collTypeIt;
	begin1.X=argBegin1.X+bitmask1.getX()/2;
	begin1.Y=argBegin1.Y+bitmask1.getY()/2-(bitmask1.getY()*bitmask1.getScaleY());
	end1.X=argBegin1.X+bitmask1.getX()/2-(bitmask1.getX()*bitmask1.getScaleX());
	end1.Y=argBegin1.Y+bitmask1.getY()/2;
	begin2.X=argBegin2.X+bitmask2.getX()/2;
	begin2.Y=argBegin2.Y+bitmask2.getY()/2-(bitmask2.getY()*bitmask2.getScaleY());
	end2.X=argBegin2.X+bitmask2.getX()/2-(bitmask2.getX()*bitmask2.getScaleX());
	end2.Y=argBegin2.Y+bitmask2.getY()/2;

//getting the intercepting box
	if(begin1.X>begin2.X) 
		interBegin.X=begin1.X;
	else
		interBegin.X=begin2.X;
	if(begin1.Y>begin2.Y) 
		interBegin.Y=begin1.Y;
	else
		interBegin.Y=begin2.Y;
	
	if(end1.X<end2.X) 
		interEnd.X=end1.X;
	else
		interEnd.X=end2.X;
	if(end1.Y<end2.Y) 
		interEnd.Y=end1.Y;
	else		interEnd.Y=end2.Y;

	collList=bitmask1.getAllCollisions(interBegin-begin1,interEnd-begin1);
	for(it= collList.begin();it!=collList.end();it++)
	{
		collTypeList=bitmask2.getAllCollisionTypes(it->getBegin(),it->getEnd());
		for(collTypeIt= collTypeList.begin();collTypeIt!=collTypeList.end();it++){
			foundTypes[(*collTypeIt)]=true;
		}
		//collTypeList.clear();
	}
	for(i=0;i<256;i++)
		if (foundTypes[i]==true)
			collTypeList.push_front(c_wall);
	return collTypeList;
}