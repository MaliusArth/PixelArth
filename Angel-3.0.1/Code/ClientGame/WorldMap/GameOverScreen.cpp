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
#include "GameOverScreen.h"

void GameOverScreen::Start()
{
    m_arth = new Actor();
    m_arth->SetSize(2.0f);
    m_arth->SetSprite("Resources/Images/animations/chars/arth/dead.png");
    m_arth->SetColor(1.0f, 1.0f, 1.0f, 0.5f);

    Actor* pitchblack = new Actor();
    pitchblack->SetSize(MathUtil::GetWorldDimensions());
    pitchblack->SetColor(0.0f, 0.0f, 0.0f, 1.0f);

    TextActor* text = new TextActor("Console","YOU DIED!\nOoooh...", TextAlignment(TXT_Center));
    text->SetPosition(0.0f,4.0f);
    text->SetColor(0,0,0);
    text->ChangeColorTo(Color(255,0,0), 2.0f, true);

    TextActor* text2 = new TextActor("Console","Retry (R)", TextAlignment(TXT_Center));
    text2->SetPosition(0.0f,-4.0f);
    text2->SetColor(0,0,0);
    text2->ChangeColorTo(Color(255,0,0), 2.0f, true);

    theWorld.Add(pitchblack, 0);
    theWorld.Add(text, 2);
    theWorld.Add(text2, 2);

    //PixelArth housekeeping below this point. 
    #pragma region PixelArth Housekeeping
    _objects.push_back(pitchblack);
    _objects.push_back(text);
    _objects.push_back(text2);

    PixelArthScreen::Start();
    #pragma endregion
}

void GameOverScreen::Update(float dt)
{
    if(theInput.IsKeyDown('r'))
    {
        theSwitchboard.Broadcast(new Message("Retry"));
    }
}
