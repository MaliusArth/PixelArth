#include "stdafx.h"

#include "PixelArthGameManager.h"
#include "Actors\GroundActor.h"

int main(int argc, char* argv[])
{
	// get things going
	//  optional parameters:
	//		int windowWidth			default: 1024
	//		int windowHeight		default: 768
	//		std::string windowName	default: "Angel Engine"
	//		bool antiAliasing		default: false
	//		bool fullScreen			default: false
	theWorld.Initialize(800, 600, "PixelArth", true, false);
	
	theWorld.SetupPhysics(Vector2::Zero);
    //theWorld.SetSideBlockers(true);
	theWorld.NameLayer("Sky", -1);
	theWorld.NameLayer("Ground", 0);

	theWorld.NameLayer("ObjectLayer 1",1);
	theWorld.NameLayer("ObjectLayer 2",2);
	theWorld.NameLayer("ObjectLayer 3",3);
	theWorld.NameLayer("ObjectLayer 4",4);
	
	theWorld.NameLayer("Front",5);
	
	//adds the default grid so you can more easily place Actors
	//theWorld.Add(new GridActor(), -2);
	//theWorld.Add(new GroundActor("Resources/Images/background.dds"), "Sky");
	
	//YOUR GAME SETUP CODE HERE
	
	theWorld.SetGameManager(&thePixelArthGame);
	
    

	
	
	
	
	
	
	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();
	
	// any cleanup can go here
	theWorld.Destroy();
	
	return 0;
}
