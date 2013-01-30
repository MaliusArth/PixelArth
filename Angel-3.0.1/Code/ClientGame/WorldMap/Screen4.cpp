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
#include "Screen4.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\SnakeActor.h"
#include "Actors\ButtonActor.h"
#include "Actors\DoorActor.h"
#include "Actors\CharActor.h"

void Screen4::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/Levels/Screen2/Screen2.png", GetBitmask("Resources/Images/Levels/Screen2/Screen2Bitmask.png"), 0.0f, MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-(MathUtil::GetWorldDimensions().X/2)+2,0));
    
    int i;

#pragma region snakes

    SnakeActor *snake[4];
    Path pos;
    pos.begin = Vector2(-3,3);
    pos.end = Vector2(-5,-3);
    snake[0] = new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.2f,3.0f);
    //pos.end = Vector2(0,4);
    //pos.begin = Vector2(0,-4);
    //snake[1]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.5f,1.0f);
    //pos.end = Vector2(0,4);
    //pos.begin = Vector2(0,-4);
    //snake[2]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.5f,1.0f);
    //pos.end = Vector2(0,4);
    //pos.begin = Vector2(0,-4);
    //snake[3]= new SnakeActor(GetBitmask("Resources/Images/animations/chars/snake/snakeBitmask.png"), pos,1.5f,1.0f);
    
#pragma endregion snakes
    
#pragma region level

#pragma region buttons

    ButtonActor *button[3];
    
    std::vector<ButtonActor *> buttons;
    button[0] = new ButtonActor("Resources/Images/Button/", GetBitmask("Resources/Images/Button/mask.png"), Vector2(-3.0f,0.0f), Vector2(1.0f), 0.5f);
    button[1] = new ButtonActor("Resources/Images/Button/", GetBitmask("Resources/Images/Button/mask.png"), Vector2(3.0f,4.0f), Vector2(2.0f));
    button[2] = new ButtonActor("Resources/Images/Button/", GetBitmask("Resources/Images/Button/mask.png"), Vector2(5.0f,-4.0f), Vector2(1.0f));
    for(i=0;i<3;++i) buttons.push_back(button[i]);

#pragma endregion buttons
    
    GroundActor* wall[18];
    DoorActor *door[2];

#pragma region left border
    wall[0] = new GroundActor("Resources/Images/Wall/wallNNEE.png", GetBitmask("Resources/Images/Wall/wallNNEE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, (MathUtil::GetWorldDimensions().Y/2)-1.0f), 2.0f);
    wall[1] = new GroundActor("Resources/Images/Wall/wallE.png", GetBitmask("Resources/Images/Wall/wallE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, (MathUtil::GetWorldDimensions().Y/2)-3.0f), 2.0f);
    wall[2] = new GroundActor("Resources/Images/Wall/wallE.png", GetBitmask("Resources/Images/Wall/wallE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, (MathUtil::GetWorldDimensions().Y/2)-5.0f), 2.0f);
    wall[3] = new GroundActor("Resources/Images/Wall/wallE.png", GetBitmask("Resources/Images/Wall/wallE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, (MathUtil::GetWorldDimensions().Y/2)-7.0f), 2.0f);
    wall[4] = new GroundActor("Resources/Images/Wall/wallSSEE.png", GetBitmask("Resources/Images/Wall/wallSSEE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, (MathUtil::GetWorldDimensions().Y/2)-9.0f), 2.0f);

    door[0] = new DoorActor("Resources/Images/Door/",GetBitmask("Resources/Images/Door/maskOpen.png"),GetBitmask("Resources/Images/Door/maskClosed.png"),
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+0.5f, (MathUtil::GetWorldDimensions().Y/2)-10.5f), Vector2(1.0f, 4.0f), true);

    wall[5] = new GroundActor("Resources/Images/Wall/wallNNEE.png", GetBitmask("Resources/Images/Wall/wallNNEE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, -2.0f), 2.0f);
    wall[6] = new GroundActor("Resources/Images/Wall/wallE.png", GetBitmask("Resources/Images/Wall/wallE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, -4.0f), 2.0f);
    wall[7] = new GroundActor("Resources/Images/Wall/wallE.png", GetBitmask("Resources/Images/Wall/wallE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, -6.0f), 2.0f);
    wall[8] = new GroundActor("Resources/Images/Wall/wallSSEE.png", GetBitmask("Resources/Images/Wall/wallSSEE_Bitmask.png"), 
        Vector2(-(MathUtil::GetWorldDimensions().X/2)+1.0f, -8.0f), 2.0f);
#pragma endregion left border

#pragma region right border
    wall[9] = new GroundActor("Resources/Images/Wall/wallNNWW.png", GetBitmask("Resources/Images/Wall/wallNNWW_Bitmask.png"), 
        (MathUtil::GetWorldDimensions()/2)-1.0f, 2.0f);
    wall[10] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-3.0f), 2.0f);
    wall[11] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-5.0f), 2.0f);
    wall[12] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-7.0f), 2.0f);
    wall[13] = new GroundActor("Resources/Images/Wall/wallSSWW.png", GetBitmask("Resources/Images/Wall/wallSSWW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, (MathUtil::GetWorldDimensions().Y/2)-9.0f), 2.0f);

    door[1] = new DoorActor("Resources/Images/Door/", GetBitmask("Resources/Images/Door/maskOpen.png"), GetBitmask("Resources/Images/Door/maskClosed.png"),
        Vector2((MathUtil::GetWorldDimensions().X/2)-0.5f, (MathUtil::GetWorldDimensions().Y/2)-10.5f), Vector2(1.0f, 4.0f) , buttons);

    wall[14] = new GroundActor("Resources/Images/Wall/wallNNWW.png", GetBitmask("Resources/Images/Wall/wallNNWW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -2.0f), 2.0f);
    wall[15] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -4.0f), 2.0f);
    wall[16] = new GroundActor("Resources/Images/Wall/wallW.png", GetBitmask("Resources/Images/Wall/wallW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -6.0f), 2.0f);
    wall[17] = new GroundActor("Resources/Images/Wall/wallSSWW.png", GetBitmask("Resources/Images/Wall/wallSSWW_Bitmask.png"), 
        Vector2((MathUtil::GetWorldDimensions().X/2)-1.0f, -8.0f), 2.0f);
#pragma endregion right border
    
#pragma endregion level

    for(i=0;i<1;++i) theWorld.Add(snake[i], i+1);
    for(i=0;i<3;++i) theWorld.Add(button[i], 1);
    for(i=0;i<2;++i) theWorld.Add(door[i], 1);
    for(i=1; i<18; ++i) theWorld.Add(wall[i], 1);

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    for(i=0;i<1;++i) _objects.push_back(snake[i]);
    for(i=0;i<3;++i) _objects.push_back(button[i]);
    for(i=0;i<2;++i) _objects.push_back(door[i]);
    for(i=0;i<18;++i) _objects.push_back(wall[i]);
    PixelArthScreen::Start();
    #pragma endregion
}