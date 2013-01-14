#include "stdafx.h"
#include "Screen1.h"

Screen1::Screen1()
{
}

//Screen1::~Screen1()
//{
//	delete m_background;
//	delete m_text;
//	delete m_hero;
//}

void Screen1::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/floating1.png", GetBitmask("Resources/Images/floating1_Bitmask.png"), MathUtil::GetWorldDimensions());
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-3,0));

    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    theWorld.Add(m_arth, "Front");

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    _objects.push_back(m_arth);

    #pragma endregion
}

void Screen1::Update(float dt)
{
    PixelArthScreen::Update(dt);
}