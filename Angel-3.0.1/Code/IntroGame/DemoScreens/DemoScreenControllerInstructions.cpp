//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2012, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DemoScreenControllerInstructions.h"

DemoScreenControllerInstructions::DemoScreenControllerInstructions()
{
}

void DemoScreenControllerInstructions::Start()
{
	//Some TextActors warning you of the hazards to come. 
	String explanation = "These next two screens show how we get input from an Xbox 360 controller";
	explanation += "\n\nIf you don't have or don't care about the controller, ";
	explanation += "\nthey'll be a little boring. Feel free to skip.";
	TextActor *t = new TextActor("Console", explanation);
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);

	theWorld.Add(t);






	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenControllerInstructions.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	#pragma endregion
}
