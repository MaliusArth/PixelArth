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
    m_ground = new GroundActor("Resources/Images/Levels/Screen1/screen1.png", GetBitmask("Resources/Images/Levels/Screen1/screen1Bitmask.png"), Vector2(0.0f), MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(0,-2));
   
    m_text = new TextActor("Console","Shit! My plane crashed!\n How do i come away from this island?",TextAlignment(TXT_Center));
    m_text->SetPosition(0.0f,4.0f);
    m_text->SetColor(0,0,0);

    GroundActor* m_propeller = new GroundActor("Resources/Images/Levels/Screen1/propeller.png", GetBitmask("Resources/Images/Levels/Screen1/propellerBitmask.png"), Vector2(-4.0f,1.0f));
    
    //We have to add it to the world for it to be drawn. All Actors implement Update and Render
    // methods that get called once per frame. All your logic should happen in the Update function,
    // and you should only implement Render if you have to do something out of the ordinary. 
	
    theWorld.Add(m_sky, "Sky");
    theWorld.Add(m_ground, "Ground");
    theWorld.Add(m_arth, "Front");
    theWorld.Add(m_text, 1);
    theWorld.Add(m_propeller, 1);

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_sky);
    _objects.push_back(m_ground);
    _objects.push_back(m_arth);
    _objects.push_back(m_text);
    _objects.push_back(m_propeller);
    PixelArthScreen::Start();
    #pragma endregion
}

void Screen1::Update(float dt)
{
    PixelArthScreen::Update(dt);
}
