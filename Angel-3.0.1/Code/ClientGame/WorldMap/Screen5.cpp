#include "stdafx.h"
#include "Screen5.h"

Screen5::Screen5()
{
}

//Screen5::~Screen5()
//{
//	delete m_background;
//	delete m_text;
//	delete m_hero;
//}

void Screen5::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/Levels/Screen3/Screen3.png", GetBitmask("Resources/Images/Levels/Screen3/Screen3Bitmask.png"), 0.0f, MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);    
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-3,0));

    m_plain =new Actor();
    m_plain->SetSprite("Resources/Images/Plain/plain2.png");
    m_plain->SetLayer(1);
    m_plain->SetPosition(0,-1);
    m_plain->SetSize(4);

    m_text = new TextActor("Console","What a luck!\n There is standing a brand new plane here!",TextAlignment(TXT_Center));
    m_text->SetPosition(0.0f,4.0f);
    m_text->SetColor(0,0,0);
    m_text->SetLayer(1);
    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    theWorld.Add(m_arth, "Front");
    theWorld.Add(m_text);
    theWorld.Add(m_plain);

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    _objects.push_back(m_arth);
    _objects.push_back(m_text);
    _objects.push_back(m_plain);
    PixelArthScreen::Start();
    #pragma endregion
}

void Screen5::Update(float dt)
{
    PixelArthScreen::Update(dt);
}