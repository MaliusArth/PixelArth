#include "stdafx.h"
#include "Screen4.h"

Screen4::Screen4()
{
}

//Screen4::~Screen4()
//{
//	delete m_background;
//	delete m_text;
//	delete m_hero;
//}

void Screen4::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/Levels/Screen2/Screen2.png", GetBitmask("Resources/Images/Levels/Screen2/Screen2Bitmask.png"), 0.0f, MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);    
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-3,0));

    Path pos;
    pos.begin = Vector2(-3,3);
    pos.end = Vector2(-5,-3);
    m_snake = new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.2f,3.0f);
    
    std::vector<ButtonActor *> buttons;
    
    m_button = new ButtonActor("Resources/Images/Button/", GetBitmask("Resources/Images/Button/mask.png"), Vector2(-3.0f,0.0f), Vector2(1.1f), 0.5f);
    buttons.push_back(m_button);

    m_buttonPerm = new ButtonActor("Resources/Images/Button/", GetBitmask("Resources/Images/Button/mask.png"), Vector2(3.0f,4.0f), Vector2(1.1f));
    buttons.push_back(m_buttonPerm);

    m_door = new DoorActor("Resources/Images/Door/",GetBitmask("Resources/Images/Door/maskOpen.png"),GetBitmask("Resources/Images/Door/maskClosed.png"),Vector2(10,0),Vector2(1.0f,3.0f),buttons);

    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    theWorld.Add(m_button, 1);
    theWorld.Add(m_buttonPerm, 1);
    theWorld.Add(m_door, 1);
    theWorld.Add(m_snake, 1);
    theWorld.Add(m_arth, "Front");

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    _objects.push_back(m_button);
    _objects.push_back(m_buttonPerm);
    _objects.push_back(m_door);
    _objects.push_back(m_snake);
    _objects.push_back(m_arth);
    PixelArthScreen::Start();
    #pragma endregion
}

void Screen4::Update(float dt)
{
    PixelArthScreen::Update(dt);
}