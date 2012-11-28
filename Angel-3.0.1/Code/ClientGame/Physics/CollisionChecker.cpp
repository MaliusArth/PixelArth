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
	begin1.X= MathUtil::WorldUnitsToPixels(argBegin1.X) + 400 - (bitmask1.getX()*bitmask1.getScaleX())/2;
	begin1.Y= MathUtil::WorldUnitsToPixels(argBegin1.Y)+300-(bitmask1.getY()*bitmask1.getScaleY())/2;// - (bitmask1.getY()*bitmask1.getScaleY());
	end1.X= MathUtil::WorldUnitsToPixels(argBegin1.X)+400 + (bitmask1.getX()*bitmask1.getScaleX())/2;
	end1.Y= MathUtil::WorldUnitsToPixels(argBegin1.Y)+300+(bitmask1.getY()*bitmask1.getScaleY())/2;
	begin2.X= MathUtil::WorldUnitsToPixels(argBegin2.X) + 400 - (bitmask2.getX()*bitmask2.getScaleX())/2;
	begin2.Y= MathUtil::WorldUnitsToPixels(argBegin2.Y)+300-(bitmask2.getY()*bitmask2.getScaleY())/2;// - (bitmask2.getY()*bitmask2.getScaleY());
	end2.X= MathUtil::WorldUnitsToPixels(argBegin2.X)+400 + (bitmask2.getX()*bitmask2.getScaleX())/2;
	end2.Y= MathUtil::WorldUnitsToPixels(argBegin2.Y)+300+(bitmask2.getY()*bitmask2.getScaleY())/2;
	
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
		collTypeList=bitmask2.getAllCollisionTypes(it->getBegin()+begin1-begin2,it->getEnd()+begin1-begin2);
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