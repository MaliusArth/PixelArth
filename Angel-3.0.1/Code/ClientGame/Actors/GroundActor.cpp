#include "StdAfx.h"
#include "GroundActor.h"


GroundActor::GroundActor(void)
{
	SetLayer(-1);
	SetSize(MathUtil::PixelsToWorldUnits(800),MathUtil::PixelsToWorldUnits(600));
	SetColor(1,1,1,1);
	this->SetSprite("Resources/Images/dummyBackground.png");
}

//void GroundActor::Update(float dt){
//}
//void GroundActor::Render(){
//}

GroundActor::~GroundActor(void)
{
}
