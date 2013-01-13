#include "StdAfx.h"
#include "Physics/CollisionHandler.h"

enum CollType
{
    c_wall = 0,
    c_snake = 78,
    c_button = 35,
    c_floor = 255
};

struct Box
{
    Vec2i begin, end;
};

//CollisionHandler::CollisionHandler()
//{
//    /*
//    Bitmask* testmask = new Bitmask("Resources/Images/animations/chars/arth/arthBitmask.png");
//
//	std::map<String, Bitmask*> m_bitmaskmap;
//
//	m_bitmaskmap.insert(make_pair(testmask->getPath(),testmask));
//
//	std::cout << "BitmaskHashmapTest: " << m_bitmaskmap.at("Resources/Images/animations/chars/arth/arthBitmask.png")->getPath() << std::endl;
//    */
//}

CollFlags CollisionHandler::checkCollisions(const Vector2& argBegin1, const Bitmask& bitmask1, const Vector2& argBegin2, const Bitmask& bitmask2) const
{
    Box m1, m2, inter;
    int i,j;
    Vec2i offset1, offset2;
    //bool foundTypes[256];
    CollFlags flags;

    //converting to bitmask coordinates
    m1.begin.X = MathUtil::WorldUnitsToPixels(argBegin1.X) + 400.f - (MathUtil::WorldUnitsToPixels(bitmask1.getSize().X)/2.f);
    m1.begin.Y=600.f - (MathUtil::WorldUnitsToPixels(argBegin1.Y) + 300.f + (MathUtil::WorldUnitsToPixels(bitmask1.getSize().Y)/2.f));// - (bitmask1.getY()*bitmask1.getScaleY());
    m1.end.X= MathUtil::WorldUnitsToPixels(argBegin1.X) + 400.f + (MathUtil::WorldUnitsToPixels(bitmask1.getSize().X)/2.f);
    m1.end.Y= 600.f - (MathUtil::WorldUnitsToPixels(argBegin1.Y) + 300.f - (MathUtil::WorldUnitsToPixels(bitmask1.getSize().Y)/2.f));

    //this is redundant work... probably could have done smoother...
    m2.begin.X= MathUtil::WorldUnitsToPixels(argBegin2.X) + 400.f - (MathUtil::WorldUnitsToPixels(bitmask2.getSize().X)/2.f);
    m2.begin.Y=600.f - (MathUtil::WorldUnitsToPixels(argBegin2.Y) + 300.f + (MathUtil::WorldUnitsToPixels(bitmask2.getSize().Y)/2.f));// - (bitmask2.getY()*bitmask2.getScaleY());
    m2.end.X= MathUtil::WorldUnitsToPixels(argBegin2.X)+400.f + (MathUtil::WorldUnitsToPixels(bitmask2.getSize().X)/2.f);
    m2.end.Y=600.f - (MathUtil::WorldUnitsToPixels(argBegin2.Y) + 300.f - (MathUtil::WorldUnitsToPixels(bitmask2.getSize().Y)/2.f));
	
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
	
    for(i=0;i<inter.end.Y-inter.begin.Y;i++)
    {
        for(j=0;j<inter.end.X-inter.begin.X;j++)
        {
            //if(bitmask1.getBit(inter.begin.X-m1.begin.X+j, inter.begin.Y-m1.begin.Y+i)!=0)
            //    std::cout <<(short int) bitmask1.getBit(inter.begin.X-m1.begin.X+i, inter.begin.Y-m1.begin.Y+j);
            if (bitmask1.getBit(inter.begin.X-m1.begin.X+j, inter.begin.Y-m1.begin.Y+i) != c_floor)
            {
                //std::cout<<(short int)bitmask1.getBit(inter.begin.X-m1.begin.X+j, inter.begin.Y-m1.begin.Y+i)<<std::endl;
                if(bitmask2.getBit(inter.begin.X-m2.begin.X+j, inter.begin.Y-m2.begin.Y+i) != c_floor)
                {
                    //std::cout<<(short int)bitmask1.getBit(inter.begin.X-m1.begin.X+j, inter.begin.Y-m1.begin.Y+i)<<std::endl;
                    switch(bitmask2.getBit(inter.begin.X-m2.begin.X+j, inter.begin.Y-m2.begin.Y+i))
                    {
                    case c_snake:
                        flags.damage = 1;
                        flags.wall = 1;
                        break;
                    case c_wall:
                        flags.wall = 1;
                        break;
                    case c_button:
                        break;
                    default:
                        break;
                    }
                    
                }
            }
            //if( bitmask2.getBit(inter.begin.X-m1.begin.X+i, inter.begin.Y-m1.begin.Y+j)==c_wall)
            //	flags.wall = 1;
            //std::cout<<bitmask2.getBit(inter.begin.X-m1.begin.X+i, inter.begin.Y-m1.begin.Y+j)<<std::endl;
        }
        //collTypeList.clear();
    }
    //std::cout<<"handler: "<<flags.wall<<std::endl;
	
    return flags;

    //if(flags.floor)
    /*
    for(i=0;i<256;i++)
        if (foundTypes[i]==true)
            collTypeList.push_front(c_wall);
    return collTypeList;
    */
}