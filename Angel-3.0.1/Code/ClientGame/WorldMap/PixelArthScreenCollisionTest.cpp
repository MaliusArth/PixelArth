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
    m_ground = new GroundActor("Resources/Images/floating1.png", GetBitmask("Resources/Images/floating1_Bitmask.png"), MathUtil::GetWorldDimensions());
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-3,0));

    Path pos;
    pos.begin = Vector2(0,2);
    pos.end = Vector2(0,-2);
    m_snake[0]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos);
    m_button = new ButtonActor("Resources/Images/Button/", GetBitmask("Resources/Images/Button/mask.png"), Vector2(2.0f), Vector2(1.0f), 1.0f);
    std::vector<ButtonActor *> buttons;
    buttons.push_back(m_button);
    m_door = new DoorActor("Resources/Images/Door/",GetBitmask("Resources/Images/Door/maskOpen.png"),GetBitmask("Resources/Images/Door/maskClosed.png"),Vector2(-1,2),Vector2(1.0f),buttons);
    pos.begin = (2, 0);
    pos.end = Vector2(-2, 0);
    m_snake[1]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos);
    pos.begin = 2;
    pos.end= -2;
    m_snake[2]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos);
    pos.begin = Vector2(2, -2);
    pos.end = Vector2(-2, 2);
    m_snake[3]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos);
    int i;

    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    theWorld.Add(m_button, 1);
    theWorld.Add(m_door, 1);
    for(i=0;i<1;++i) theWorld.Add(m_snake[i], i+1);
    theWorld.Add(m_arth, "Front");

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    _objects.push_back(m_button);
    _objects.push_back(m_door);
    for(i=0;i<1;++i) _objects.push_back(m_snake[i]);
    _objects.push_back(m_arth);

    #pragma endregion
}

void PixelArthScreenCollisionTest::Update(float dt)
{
    PixelArthScreen::Update(dt);
}