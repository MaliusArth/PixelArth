#include "stdafx.h"
#include "Screen2.h"

Screen2::Screen2()
{
}

//Screen2::~Screen2()
//{
//	delete m_background;
//	delete m_text;
//	delete m_hero;
//}

void Screen2::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/Levels/Screen2/Screen2.png", GetBitmask("Resources/Images/Levels/Screen2/Screen2Bitmask.png"), 0.0f, MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);    
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-3,0));

    Path pos;
    pos.begin = Vector2(-2,4);
    pos.end = Vector2(-2,-4);
    m_snake[0]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,2.0f,2.3f);
    pos.end = Vector2(0,4);
    pos.begin = Vector2(0,-4);
    m_snake[1]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.5f,1.0f);
    pos.begin = Vector2(2,4);
    pos.end = Vector2(2,-4);
    m_snake[2]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.7f,2.0f);
    pos.begin = Vector2(-2,4);
    pos.end = Vector2(2,-4);
    m_snake[3]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,3.0f,4.0f);
    int i;

    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    for(i=0;i<4;++i) theWorld.Add(m_snake[i], i+1);
    theWorld.Add(m_arth, "Front");

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    for(i=0;i<4;++i) _objects.push_back(m_snake[i]);
    _objects.push_back(m_arth);
    PixelArthScreen::Start();
    #pragma endregion
}

void Screen2::Update(float dt)
{
    PixelArthScreen::Update(dt);
}