#include "stdafx.h"
#include "PixelArthScreenCharTest.h"

PixelArthScreenCharTest::PixelArthScreenCharTest()
{
}

//PixelArthScreenCharTest::~PixelArthScreenCharTest()
//{
//}

void PixelArthScreenCharTest::Start()
{
	//Creating a new, generic actor is simple.

	//m_a = new Actor();
	arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"));
	arth->SetName("Arth");
	//Sizes and coordinates are always in GL units, which can mean whatever you decide they mean
	// -- our physics packages (Box2D) assumes that they mean meters, though. 
	//a->SetSize(2.0f);
	
	//R, G, B, [A]
	//a->SetColor(0,0,0);

	//a->SetColor(1,1,1,1); //(white and opaque so the texture comes through fully)
	//a->ClearSpriteInfo();
	//a->SetSprite("Resources/Images/animations/chars/arth/standing.png");

	//We have to add it to the world for it to be drawn. All Actors implement Update and Render
	// methods that get called once per frame. All your logic should happen in the Update function,
	// and you should only implement Render if you have to do something out of the ordinary. 
	theWorld.Add(arth);
	
	//Bitmask* testmask = new Bitmask("Resources/Images/animations/chars/arth/arthBitmask.png");

	//std::map<String, Bitmask*> testmap;

	//testmap.insert(make_pair(testmask->getPath(),testmask));

	//std::cout << "BitmaskHashmapTest: " << testmap.at("Resources/Images/animations/chars/arth/arthBitmask.png")->getPath() << std::endl;

	//PixelArth housekeeping below this point. 
	#pragma region PixelArth Housekeeping
	t = new TextActor("Console", "That's Arth. (Press [X])");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "PixelArthScreenCharTest.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(10, 563));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(arth);
	#pragma endregion
}

void PixelArthScreenCharTest::Update(float dt)
{
	if ((theController.IsConnected() && theController.IsBButtonDown()) || theInput.IsKeyDown('b'))
	{
		//a->SetColor(1.0f, 0.0f, 1.0f, .5f); //R, G, B, A (there is also a Color class you can use)
		//a->ClearSpriteInfo(); //removes any texture that might have been assigned
		t->SetDisplayString("Now it's purple and translucent. Press [Y] to give it a texture.");
	}
	if ((theController.IsConnected() && theController.IsYButtonDown()) || theInput.IsKeyDown('y'))
	{
		//a->SetColor(1,1,1,1); //(white and opaque so the texture comes through fully)
		//a->ClearSpriteInfo();
		//a->SetSprite("Resources/Images/animations/chars/arth/standing.png"); //Loads any image supported by DevIL (see docs)
		t->SetDisplayString("Pretty easy. You can do animations as well. Press [X] to check it out.");
	}
	if ((theController.IsConnected() && theController.IsXButtonDown()) || theInput.IsKeyDown('x'))
	{
		//a->SetColor(1,1,1,1);
		//a->LoadSpriteFrames("Resources/Images/animations/chars/arth/standing2/standing2_0.png");
		//a->PlaySpriteAnimation(
		//	0.2f,			//amount of time between frames
		//	SAT_Loop,		//other options are SAT_PingPong and SAT_OneShot
		//	0,				//starting frame
		//	8,				//ending frame
		//	"Standing"	//name of the animation so you can get the event when it finishes
		//);
		t->SetDisplayString("Keiner mag den Hufi =/");
	}
}
