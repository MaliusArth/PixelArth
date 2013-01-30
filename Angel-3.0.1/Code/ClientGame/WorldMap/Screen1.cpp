/////////////////////////////////////////////////////////////////////////
// PixelArth
// Copyright (C) 2012  Viktor Was <viktor.was@technikum-wien.at>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Screen1.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
#include "Actors\TextActor.h"
#include "Actors\CharActor.h"

void Screen1::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/Levels/Screen1/screen1.png", GetBitmask("Resources/Images/Levels/Screen1/screen1Bitmask.png"), Vector2(0.0f), MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(0,-2));
	
    TextActor *text;
    text = new TextActor("Console","My plane... crashed... \nI... survived...!?\nNeed to find... a away...from this floating island?",TXT_Center);
    text->SetPosition(0.0f,4.0f);
    text->SetColor(0,0,0);
    
    int i;

#pragma region level

    GroundActor* m_propeller = new GroundActor("Resources/Images/Levels/Screen1/propeller.png", GetBitmask("Resources/Images/Levels/Screen1/propellerBitmask.png"), Vector2(-4.0f,1.0f));

    GroundActor* wall[9];
    
#pragma region right border
    wall[0] = new GroundActor("Resources/Images/Wall/wallNNWW.png", GetBitmask("Resources/Images/Wall/wallNNWW_Bitmask.png"), 
        (MathUtil::GetWorldDimensions()/2)-1.0f, 2.0f);
    wall[1] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-3.0f), 2.0f);
    wall[2] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-5.0f), 2.0f);
    wall[3] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-7.0f), 2.0f);
    wall[4] = new GroundActor("Resources/Images/Wall/wallSSWW.png", GetBitmask("Resources/Images/Wall/wallSSWW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-9.0f), 2.0f);

    wall[5] = new GroundActor("Resources/Images/Wall/wallNNWW.png", GetBitmask("Resources/Images/Wall/wallNNWW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -2.0f), 2.0f);
    wall[6] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -4.0f), 2.0f);
    wall[7] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -6.0f), 2.0f);
    wall[8] = new GroundActor("Resources/Images/Wall/wallSSWW.png", GetBitmask("Resources/Images/Wall/wallSSWW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -8.0f), 2.0f);
#pragma endregion right border

#pragma endregion level

    theWorld.Add(m_propeller, 1);
    theWorld.Add(text, 2);
    for(i=1; i<9; ++i) theWorld.Add(wall[i], 1);
    
    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(m_propeller);
    _objects.push_back(text);
    for(i=0;i<9;++i) _objects.push_back(wall[i]);
    PixelArthScreen::Start();
    #pragma endregion
}