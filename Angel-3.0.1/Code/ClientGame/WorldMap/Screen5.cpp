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
#include "Screen5.h"

#include "Actors\CloudActor.h"
#include "Actors\GroundActor.h"
#include "Actors\CharActor.h"

void Screen5::Start()
{
    m_sky = new CloudActor("Resources/Images/clouds2.jpg");
    m_ground = new GroundActor("Resources/Images/Levels/Screen3/Screen3.png", GetBitmask("Resources/Images/Levels/Screen3/Screen3Bitmask.png"), 0.0f, MathUtil::GetWorldDimensions());
    m_ground->SetLayered(false);
    m_arth = new CharActor(GetBitmask("Resources/Images/animations/chars/arth/arthBitmask.png"),Vector2(-(MathUtil::GetWorldDimensions().X/2)+2,0));
    
    m_plain = new GroundActor("Resources/Images/Plain/plain2.png", GetBitmask("Resources/Images/Plain/plain2_Bitmask.png"), Vector2(0,-1), 4);
    m_plain->SetLayered(false);

    TextActor *text;
    text = new TextActor("Console","What a luck!\n There is standing a brand new plane here!",TXT_Center);
    text->SetPosition(0.0f,4.0f);
    text->SetColor(0,0,0);
    
    theWorld.Add(text, 500);
    theWorld.Add(m_plain, 1);

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(text);
    _objects.push_back(m_plain);

    PixelArthScreen::Start();
    #pragma endregion
}

void Screen5::Update(float dt)
{
    if(m_plain->IsColliding())
    {
        theWorld.StopGame();
    }
}