#include "StdAfx.h"
#include "CollisionChecker.h"

struct IntVector{
	int X, Y;
};
struct Box{
	IntVector begin, end;
};

CollFlags CollisionChecker::checkCollisions(const Vector2& argBegin1,const Bitmask2& bitmask1, const Vector2& argBegin2, const Bitmask2& bitmask2) const{
	Box m1, m2, inter;
	int i,j;
	IntVector offset1, offset2;
	bool foundTypes[256];
	CollFlags flags;
	//converting to bitmask coordinates
	m1.begin.X= MathUtil::WorldUnitsToPixels(argBegin1.X) + 400 - (bitmask1.getSizeX())/2;
	m1.begin.Y=600-  MathUtil::WorldUnitsToPixels(argBegin1.Y)+300 - (bitmask1.getSizeY())/2;// - (bitmask1.getY()*bitmask1.getScaleY());
	m1.end.X= MathUtil::WorldUnitsToPixels(argBegin1.X)+400 + (bitmask1.getSizeX())/2;
	m1.end.Y= 600-MathUtil::WorldUnitsToPixels(argBegin1.Y)+300 + (bitmask1.getSizeY())/2;

	//this is redundant work... probably could have done smoother...
	m2.begin.X= MathUtil::WorldUnitsToPixels(argBegin2.X)+400 - (bitmask2.getSizeX())/2;
	m2.begin.Y=600- MathUtil::WorldUnitsToPixels(argBegin2.Y)+300 - (bitmask2.getSizeY())/2;// - (bitmask2.getY()*bitmask2.getScaleY());
	m2.end.X= MathUtil::WorldUnitsToPixels(argBegin2.X)+400 + (bitmask2.getSizeX())/2;
	m2.end.Y=600- MathUtil::WorldUnitsToPixels(argBegin2.Y)+300 + (bitmask2.getSizeY())/2;
	
//getting the intercepting box
//begin
	if(m1.begin.X>m2.begin.X) 
		inter.begin.X=m1.begin.X;
	else
		inter.begin.X=m2.begin.X;
	if(m1.begin.Y>m2.begin.Y) 
		inter.begin.Y=m1.begin.Y;
	else
		inter.begin.Y=m2.begin.Y;
//and the ending... very reduntant again =/
	if(m1.end.X<m2.end.X) 
		inter.end.X=m1.end.X;
	else
		inter.end.X=m2.end.X;
	if(m1.end.Y<m2.end.Y) 
		inter.end.Y=m1.end.Y;
	else		
		inter.end.Y=m2.end.Y;

	for(i=0;i<inter.end.X-inter.begin.X;i++)
	{
		for(j=0;j<inter.end.Y-inter.begin.Y;j++){
			if(bitmask1.getBit(inter.begin.X-m1.begin.X+i, inter.begin.Y-m1.begin.Y+j)!=c_floor)
					if(bitmask2.getBit(inter.begin.X-m2.begin.X+i, inter.begin.Y-m2.begin.Y+j) != c_floor)
		//	std::cout<<"ich war hier"<<std::endl;
				flags.wall = 1;
			/*	if( bitmask2.getBit(inter.begin.X-m1.begin.X+i, inter.begin.Y-m1.begin.Y+j)==c_wall)
					
					flags.wall = 1;*/
				//std::cout<<bitmask2.getBit(inter.begin.X-m1.begin.X+i, inter.begin.Y-m1.begin.Y+j)<<std::endl;
			
		}
		//collTypeList.clear();
	}

	return flags;

	//if(flags.floor)
/*	for(i=0;i<256;i++)
		if (foundTypes[i]==true)
			collTypeList.push_front(c_wall);
	return collTypeList;'*/
}