#include "stdafx.h"
#include "PixelArthScreenCollisionTest.h"

PixelArthScreenCollisionTest::PixelArthScreenCollisionTest()
{
}

//PixelArthScreenCollisionTest::~PixelArthScreenCollisionTest()
//{
//	delete m_background;
//	delete m_text;
//	delete m_hero;
//}

void PixelArthScreenCollisionTest::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/floating1_Bitmask.png", GetBitmask("Resources/Images/floating1_Bitmask.png"));
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"));

    /*Path pos;
    pos.begin = Vector2(0,2);
    pos.end = Vector2(0,-2);
    m_snake[0]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/arthBitmask.png"), pos);
    pos.begin = (2, 0);
    pos.end = Vector2(-2, 0);
    m_snake[1]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/arthBitmask.png"), pos);
    pos.begin = 2;
    pos.end= -2;
    m_snake[2]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/arthBitmask.png"), pos);
    pos.begin = Vector2(2, -2);
    pos.end = Vector2(-2, 2);
    m_snake[3]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/arthBitmask.png"), pos);
    int i;*/

    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    //for(i=0;i<4;++i) theWorld.Add(m_snake[i], i+1);
    theWorld.Add(m_arth, "Front");

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    //for(i=0;i<4;++i) _objects.push_back(m_snake[i]);
    _objects.push_back(m_arth);
    #pragma endregion
}

void PixelArthScreenCollisionTest::Update(float dt)
{
    PixelArthScreen::Update(dt);
}