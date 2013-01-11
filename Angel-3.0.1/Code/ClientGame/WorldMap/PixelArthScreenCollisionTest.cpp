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
	m_sky = new CloudActor("Resources/Images/clouds2.jpg");
	m_ground = new GroundActor("Resources/Images/floating1.png");
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"));
    theSwitchboard.SubscribeTo(m_arth,"CollisionStartWith"+m_arth->GetName());
    theSwitchboard.SubscribeTo(m_arth,"CollisionEndWith"+m_arth->GetName());

    if(m_arth->GetBody() != NULL){
    //std::cout << "data: " << static_cast<CharActor*>(m_arth->GetBody()->GetUserData())->GetMask()->getPath() << std::endl;
    }
	Path pos;
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
	int i;

	//We have to add it to the world for it to be drawn. All Actors implement Update and Render
	// methods that get called once per frame. All your logic should happen in the Update function,
	// and you should only implement Render if you have to do something out of the ordinary. 

    //theWorld.BeginContact();
	
	theWorld.Add(m_arth, "Front");
	for(i=1;i<=4;i++)theWorld.Add(m_snake[i], 1);
	theWorld.Add(m_sky, "Sky");
	theWorld.Add(m_ground, "Ground");

	//PixelArth housekeeping below this point. 
	#pragma region PixelArth Housekeeping
	_objects.push_back(m_sky);
	_objects.push_back(m_ground);
	for(i=0;i<4;++i) _objects.push_back(m_snake[i]);
	_objects.push_back(m_arth);
	#pragma endregion
}

void PixelArthScreenCollisionTest::Update(float dt)
{
    PixelArthScreen::Update(dt);
}