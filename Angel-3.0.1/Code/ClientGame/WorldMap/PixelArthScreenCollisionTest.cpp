#include "stdafx.h"
#include "PixelArthScreenCollisionTest.h"


PixelArthScreenCollisionTest::PixelArthScreenCollisionTest()
{
	//thePixelArthGame.m_wColl->setBitmask("Resources/Images/coll.png");
}

//PixelArthScreenCollisionTest::~PixelArthScreenCollisionTest()
//{
//	delete m_background;
//	delete m_text;
//	delete m_hero;
//}
void PixelArthScreenCollisionTest::Start()
{
	m_hero = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"));
	m_background = new GroundActor("Resources/Images/floating1.png");
	//m_background->SetLayer(-10);
	m_background2= new CloudActor("Resources/Images/clouds2.jpg");
	Path pos;
	pos.begin.X= 0;
	pos.begin.Y= 2;
	pos.end.X= 0;
	pos.end.Y=-2;
	m_snake[0]= new SnakeActor(pos);
	pos.begin.X= 2;
	pos.begin.Y= 0;
	pos.end.X= -2;
	pos.end.Y=0;
	m_snake[1]= new SnakeActor(pos);
	pos.begin = 2;
	pos.end= -2;
	m_snake[2]= new SnakeActor(pos);
	pos.begin.X= 2;
	pos.begin.Y= -2;
	pos.end.X= -2;
	pos.end.Y=2;
	m_snake[3]= new SnakeActor(pos);
	int i;
	for(i=0;i<4;i++)m_snake[i]->SetLayer(0);
	//m_text = new TextActor("Console", "Collision Test");
	//Creating a new, generic actor is simple. 
	
	
	//Sizes and coordinates are always in GL units, which can mean whatever you decide they mean
	// -- our physics packages (Box2D) assumes that they mean meters, though. 
	//m_hero->SetSize(2.0f); 
	
	//R, G, B, [A]
	//a->SetColor(0,0,0);

	//m_hero->SetColor(1,1,1,1); //(white and opaque so the texture comes through fully)
	//a->ClearSpriteInfo();
	//m_hero->SetSprite("Resources/Images/animations/chars/arth/standing.png");

	//We have to add it to the world for it to be drawn. All Actors implement Update and Render
	// methods that get called once per frame. All your logic should happen in the Update function,
	// and you should only implement Render if you have to do something out of the ordinary. 
	theWorld.Add(m_hero);
	
	theWorld.Add(m_background2);
	theWorld.Add(m_background);
	for(i=0;i<4;i++)theWorld.Add(m_snake[i]);



	//PixelArth housekeeping below this point. 
	#pragma region PixelArth Housekeeping
	//m_text->SetPosition(0, 3.5);
	//m_text->SetAlignment(TXT_Center);
	//theWorld.Add(m_text);
	//TextActor *fileLoc = new TextActor("ConsoleSmall", "PixelArthScreenCharTest.cpp");
	//fileLoc->SetPosition(MathUtil::ScreenToWorld(10, 563));
	//fileLoc->SetColor(.3f, .3f, .3f);
	//theWorld.Add(fileLoc);
	//_objects.push_back(fileLoc);
	//_objects.push_back(m_text);
	_objects.push_back(m_background2);
	_objects.push_back(m_background);
	_objects.push_back(m_hero);
	for(i=0;i<4;i++)_objects.push_back(m_snake[i]);
	#pragma endregion
}

void PixelArthScreenCollisionTest::Update(float dt)
{
	
}