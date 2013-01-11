#include "StdAfx.h"
#include "GroundActor.h"

GroundActor::GroundActor(const String& picturefile)
{
	SetLayer("Ground");
	SetSize(MathUtil::GetWorldDimensions());    //MathUtil::PixelsToWorldUnits(800),MathUtil::PixelsToWorldUnits(600)
	SetColor(1,1,1,1);
	SetSprite(picturefile);
}

//void GroundActor::Update(float dt){
//}
//void GroundActor::Render(){
//}
//
//GroundActor::~GroundActor(void)
//{
//}
