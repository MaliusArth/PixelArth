#include "stdafx.h"

#include "Infrastructure/Camera.h"
#include "Util/StringUtil.h"
#include "Util/MathUtil.h"
#include "Messaging/Switchboard.h"
#include "Util/DrawUtil.h"

//built-in loggers are pretty poor
#include "Infrastructure/Log.h"

#include "CharActor.h"
#include "PixelArthGameManager.h"
#include <iostream>

#define IDLE_TIME 5.0f

CharActor::CharActor(Bitmask * const mask, const Vector2 size)
	: CollidingActor(mask, size)
	, m_direction(SOUTH)
	, m_moving(false)
	, m_movingNorth(false)
	, m_movingEast(false)
	, m_movingSouth(false)
	, m_movingWest(false)
	, m_movementSpeed(3.0f)
	, m_idleness(0.0f)
	, m_idleAnim(false)
	//, m_isKinematic(true)
{
    SetName("Arth");
	//SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    SetSize(size.X, size.Y);
    m_mask->setSize(size);

    m_bBox = BoundingBox(Vector2(GetPosition().X-(_size.X/2), GetPosition().Y-(_size.Y/2)),
                         Vector2(GetPosition().X+(_size.X/2), GetPosition().Y+(_size.Y/2)));
    //m_bBox.RenderBox();       //not working?
    //m_bBox.RenderOutline();   //not working?
    
    /*if(GetBody() != NULL){
        std::cout << "charactor ctor getbody succeeded!" << std::endl;
        GetBody()->SetUserData(m_mask);
    }*/
	
	//_timestampArrowReleased = theWorld.GetCurrentTimeSeconds();

	//ClearSpriteInfo();
	SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");

	///TEST
	//_world = new Bitmask("Resources/Images/coll.png");
    
	SetDensity(1.0f);
	SetFriction(0.0f);
	SetRestitution(0.0f);
	//SetIsSensor(true);
	SetFixedRotation(true);
	InitPhysics();

	theSwitchboard.SubscribeTo(this, "CameraChange");
	theSwitchboard.SubscribeTo(this, "UpArrowPressed");
	theSwitchboard.SubscribeTo(this, "DownArrowPressed");
	theSwitchboard.SubscribeTo(this, "LeftArrowPressed");
	theSwitchboard.SubscribeTo(this, "RightArrowPressed");
	theSwitchboard.SubscribeTo(this, "UpArrowReleased");
	theSwitchboard.SubscribeTo(this, "DownArrowReleased");
	theSwitchboard.SubscribeTo(this, "LeftArrowReleased");
	theSwitchboard.SubscribeTo(this, "RightArrowReleased");
}

CharActor::~CharActor(void)
{
    delete m_mask;
}

void CharActor::Update(float dt)
{
	CollidingActor::Update(dt);

    m_bBox.Min = Vector2(GetPosition().X-(_size.X/2), GetPosition().Y-(_size.Y/2));
    m_bBox.Max = Vector2(GetPosition().X+(_size.X/2), GetPosition().Y+(_size.Y/2));

    //IsColliding();
    
    //iterate through contacts, get other userdata and call own collision
    //PhysicsActor* other = static_cast<PhysicsActor*>(GetBody()->GetContactList()->other->GetUserData());
    //theWorld.GetPhysicsWorld().
	
    //SetLayer(-MathUtil::WorldUnitsToPixels(GetPosition().Y-(GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2));
	
    float delay = 0.1f;
	spriteAnimationType animType = SAT_None;
	int startFrame = 0;
	int endFrame = 0;
	String animName = String();
	///HUUUUUUFFFFIIIIII
	Vector2 direction = Vector2::Zero;
	if(m_movingNorth)
	{
		direction.Y += 1.0f;
	}
	if(m_movingEast)
	{
		direction.X += 1.0f;
	}
	if(m_movingSouth)
	{
		direction.Y -= 1.0f;
	}
	if(m_movingWest)
	{
		direction.X -= 1.0f;
	}
	direction != Vector2::Zero ? m_moving=true : m_moving=false;
	if(m_moving)
	{
		float angle_rad = MathUtil::AngleFromVector(direction);
		//bug fix along axes:
		direction.X = direction.X == 0 ? 0 : (m_movementSpeed)*cos(angle_rad);
		direction.Y = direction.Y == 0 ? 0 : (m_movementSpeed/2)*sin(angle_rad);
		m_idleness = 0.0f;
	}
	Vector2 newPosition = _position + direction;
	///
	bool collType = false;//thePixelArthGame.m_wColl->isColliding(*m_mask, newPosition-(GetSize()/2));

	//std::cout << "moving: " << m_moving << " collType: " << collType << std::endl;

	//bool collType = false;
	if(m_moving)
	{
		if((newPosition.Y > _position.Y) & (newPosition.X == _position.X))
		{
			m_direction = NORTH;
		}
		else if((newPosition.X > _position.X) & (newPosition.Y > _position.Y))
		{
			m_direction = NORTHEAST;
		}
		else if((newPosition.X > _position.X) & (newPosition.Y == _position.Y))
		{
			m_direction = EAST;
		}
		else if((newPosition.X > _position.X) & (newPosition.Y < _position.Y))
		{
			m_direction = SOUTHEAST;
		}
		else if((newPosition.Y < _position.Y) & (newPosition.X == _position.X))
		{
			m_direction = SOUTH;
		}
		else if((newPosition.X < _position.X) & (newPosition.Y < _position.Y))
		{
			m_direction = SOUTHWEST;
		}
		else if((newPosition.X < _position.X) & (newPosition.Y == _position.Y))
		{
			m_direction = WEST;
		}
		else if((newPosition.X < _position.X) & (newPosition.Y > _position.Y))
		{
			m_direction = NORTHWEST;
		}
	}
    
    //if(m_moving && m_collFlags.floor)
	if(m_moving && !collType)
	{
		m_idleAnim = false;
	
		#pragma region Walk North
		if((newPosition.Y > _position.Y) & (newPosition.X == _position.X))
		{
			if(_currentAnimName.compare("WalkUp") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/up/walkUp_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUp";
			}
		}
		#pragma endregion Walk North
		#pragma region Walk North-East
		if((newPosition.X > _position.X) & (newPosition.Y > _position.Y))
		{
			if(_currentAnimName.compare("WalkUpRight") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/upRight/walkUpRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUpRight";
			}
		}
		#pragma endregion Walk North-East
		#pragma region Walk East
		if((newPosition.X > _position.X) & (newPosition.Y == _position.Y))
		{
			if(_currentAnimName.compare("WalkRight") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/right/walkRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkRight";
			}
		}
		#pragma endregion Walk East
		#pragma region Walk South-East
		if((newPosition.X > _position.X) & (newPosition.Y < _position.Y))
		{
			if(_currentAnimName.compare("WalkDownRight") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/downRight/walkDownRight_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkDownRight";
			}
		}
		#pragma endregion Walk South-East
		#pragma region Walk South
		if((newPosition.Y < _position.Y) & (newPosition.X == _position.X))
		{
			if(_currentAnimName.compare("WalkDown") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/down/walkDown_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;
				animName = "WalkDown";
			}
		}
		#pragma endregion Walk South
		#pragma region Walk South-West
		if((newPosition.X < _position.X) & (newPosition.Y < _position.Y))
		{
			if(_currentAnimName.compare("WalkDownLeft") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/downLeft/walkDownLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkDownLeft";
			}
		}
		#pragma endregion Walk South-West
		#pragma region Walk West
		if((newPosition.X < _position.X) & (newPosition.Y == _position.Y))
		{
			if(_currentAnimName.compare("WalkLeft") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/left/walkLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;
				animName = "WalkLeft";
			}
		}
		#pragma endregion Walk West
		#pragma region Walk North-West
		if((newPosition.X < _position.X) & (newPosition.Y > _position.Y))
		{
			if(_currentAnimName.compare("WalkUpLeft") != 0)
			{
				ClearSpriteInfo();
				LoadSpriteFrames("Resources/Images/animations/chars/arth/walk/upLeft/walkUpLeft_00.png");
				delay = 0.1f;
				animType = SAT_Loop;
				startFrame = 0;
				endFrame = 5;	
				animName = "WalkUpLeft";
			}
		}
		#pragma endregion Walk North-West
	}
	/*else if(collType == 0)	//make enum for collType
	{
		
	}*/
    
    //if(!m_moving || !m_collFlags.floor)
	if(!m_moving || collType)
	{
		m_idleness+=dt;
		if(m_idleness < IDLE_TIME)
		{
			if(!m_idleAnim)
			{
				switch(m_direction)
				{
				case NORTH:
					if(_currentAnimName.compare("LookAroundUp") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						//CLAMPMODES: GL_CLAMP or GL_REPEAT
						//FILTERMODES: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, or 
						//GL_LINEAR_MIPMAP_LINEAR
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUp/lookAroundUp_00.png"/*, 0, GL_CLAMP, GL_LINEAR_MIPMAP_NEAREST*/);
					}
					break;
				case NORTHEAST:
					if(_currentAnimName.compare("LookAroundUpRight") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUpRight/lookAroundUpRight_00.png");
					}
					break;
				case EAST:
					if(_currentAnimName.compare("LookAroundRight") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundRight/lookAroundRight_00.png");
					}
					break;
				case SOUTHEAST:
					if(_currentAnimName.compare("LookAroundDownRight") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDownRight/lookAroundDownRight_00.png");
					}
					break;
				case SOUTH:
					if(_currentAnimName.compare("LookAroundDown") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
					}
					break;
				case SOUTHWEST:
					if(_currentAnimName.compare("LookAroundDownLeft") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundDownLeft/lookAroundDownLeft_00.png");
					}
					break;
				case WEST:
					if(_currentAnimName.compare("LookAroundLeft") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundLeft/lookAroundLeft_00.png");
					}
					break;
				case NORTHWEST:
					if(_currentAnimName.compare("LookAroundUpLeft") != 0)
					{	
						ClearSpriteInfo();
						_currentAnimName = "";
						SetSprite("Resources/Images/animations/chars/arth/stand/lookAroundUpLeft/lookAroundUpLeft_00.png");
					}
					break;
				}
			}
		}
		else
		{
			m_idleness=0.0f;
			m_idleAnim = true;
			switch(m_direction)
			{
			case NORTH:
				if(_currentAnimName.compare("LookAroundUp") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundUp/lookAroundUp_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundUp";
				}
				break;
			case NORTHEAST:
				if(_currentAnimName.compare("LookAroundUpRight") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundUpRight/lookAroundUpRight_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundUpRight";
				}
				break;
			case EAST:
				if(_currentAnimName.compare("LookAroundRight") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundRight/lookAroundRight_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundRight";
				}
				break;
			case SOUTHEAST:
				if(_currentAnimName.compare("LookAroundDownRight") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDownRight/lookAroundDownRight_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundDownRight";
				}
				break;
			case SOUTH:
				if(_currentAnimName.compare("LookAroundDown") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDown/lookAroundDown_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundDown";
				}
				break;
			case SOUTHWEST:
				if(_currentAnimName.compare("LookAroundDownLeft") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundDownLeft/lookAroundDownLeft_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundDownLeft";
				}
				break;
			case WEST:
				if(_currentAnimName.compare("LookAroundLeft") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundLeft/lookAroundLeft_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundLeft";
				}
				break;
			case NORTHWEST:
				if(_currentAnimName.compare("LookAroundUpLeft") != 0)
				{
					ClearSpriteInfo();
					LoadSpriteFrames("Resources/Images/animations/chars/arth/stand/lookAroundUpLeft/lookAroundUpLeft_00.png");
					delay = 0.2f;
					animType = SAT_OneShot;
					startFrame = 0;
					endFrame = 9;
					animName = "LookAroundUpLeft";
				}
				break;
			}
		}
	}

	if((_currentAnimName.compare(animName) != 0) & !IsSpriteAnimPlaying())
	{
		PlaySpriteAnimation(
			delay,					//amount of time between frames
			animType,				//other options are SAT_PingPong and SAT_OneShot
			startFrame,				//starting frame
			endFrame,				//ending frame
			animName.c_str()		//name of the animation so you can get the event when it finishes
		);
	}

    //if(m_moving & m_collFlags.floor)
	if(m_moving && !collType)
	{
		//_position = newPosition;		//TODO: check for memory leak
		//GetBody()->SetLinearVelocity(b2Vec2(direction.X, direction.Y));
	
		//ApplyForce(dt, newPosition);	//BUGGY
		//MoveTo(newPosition, dt);
        
	}
    std::cout << "none: " << m_collFlags.none << std::endl;
    std::cout << "floor: " << m_collFlags.floor << std::endl;
    std::cout << "wall: " << m_collFlags.wall << std::endl;
    if(m_collFlags.none)
        std::cout << "none" << std::endl;
    
    if(m_collFlags.floor)
        std::cout << "floor" << std::endl;
    
    if(m_collFlags.wall)
        std::cout << "wall" << std::endl;

    if(m_moving && collType)
    {
        direction = Vector2::Zero;
    }
    if (GetBody() != NULL)
	    GetBody()->SetLinearVelocity(b2Vec2(direction.X, direction.Y));
}

void CharActor::AnimCallback(String animName)
{
	_currentAnimName = "";
	//only if idle animation
	m_idleAnim = false;
	/*if(animName.compare("LookAroundDown") == 0)
	{

	}*/
}

void CharActor::ReceiveMessage(Message* m)
{
    std::cout << "CharActor recieved Msg: " << m->GetMessageName() << std::endl;
	if (m->GetMessageName() == "CameraChange")
	{
	}

    /*if (m->GetMessageName() == "CollisionStartWith"+GetName())
    {
        m_colliding = true;
        std::cout << "coll test: " + GetName() << std::endl;
        //
        //TypedMessage<b2Contact*>* coll = dynamic_cast<TypedMessage<b2Contact*>*>(m);

        ////TypedMessage<b2Contact*>* coll = new TypedMessage<b2Contact*>(pa1Message, contact, pa2);
        //b2Contact* b2c = coll->GetValue();

        //CollidingActor* pa = static_cast<CollidingActor*>(b2c->GetFixtureA()->GetBody()->GetUserData());
        //CollidingActor* pb = static_cast<CollidingActor*>(b2c->GetFixtureB()->GetBody()->GetUserData());
        //
        //std::cout << "Test NameA: " << pa->GetName() << std::endl;
        //std::cout << "Test NameB: " << pb->GetName() << std::endl;
        //thePixelArthGame.m_collHandler->checkCollisions(pa->GetPosition(), pa->GetMask(), pb->GetPosition(), pb->GetMask());
        

        /// no need for collision messages...simply put this in CollidingActor::Update (CollidingActor::Update calls PhysicsActor::Update too)
        //CollidingActor *ca;
        //b2ContactEdge* contactlist = GetBody()->GetContactList();
        //while(contactlist!=NULL)
        //{
        //ca = static_cast<CollidingActor *>(contactlist->other->GetUserData());
        //std::cout << "char contacts with " << ca->GetName() << std::endl;
        //contactlist = contactlist->next;
        //}
    }
    */

#pragma region Animation Ended messages

	/*if (m->GetMessageName() == "Standing")
	{
		std::cout << "Standing" << std::endl;
	}*/

#pragma endregion
	
#pragma region Key-Down messages

	if (m->GetMessageName() == "UpArrowPressed")
	{
		//SystemLog().Log("UpArrowPressed");
		m_movingNorth = true;
	}
	if (m->GetMessageName() == "DownArrowPressed")
	{
		m_movingSouth = true;
	}
	if (m->GetMessageName() == "LeftArrowPressed")
	{
		m_movingWest = true;
	}
	if (m->GetMessageName() == "RightArrowPressed")
	{
		m_movingEast = true;
	}

#pragma endregion

#pragma region Key-Up messages

	if (m->GetMessageName() == "UpArrowReleased")
	{
		//SystemLog().Log("UpArrowReleased");
		m_movingNorth = false;

		/*if(theWorld.GetCurrentTimeSeconds() - _timestampArrowReleased < 0.02f)
		{

		}*/
		/*std::cout << "UP after RIGHT " << theWorld.GetCurrentTimeSeconds() - _timestampArrowReleased << std::endl;
		_timestampArrowReleased = theWorld.GetCurrentTimeSeconds();*/
	}
	if (m->GetMessageName() == "DownArrowReleased")
	{
		m_movingSouth = false;
	}
	if (m->GetMessageName() == "LeftArrowReleased")
	{
		m_movingWest = false;
	}
	if (m->GetMessageName() == "RightArrowReleased")
	{
		m_movingEast = false;

		/*if(theWorld.GetCurrentTimeSeconds() - _timestampArrowReleased < 0.02f)
		{

		}*/
		//std::cout << "RIGHT after UP " << theWorld.GetCurrentTimeSeconds() - m_timestampArrowReleased << std::endl;
		m_timestampArrowReleased = theWorld.GetCurrentTimeSeconds();
	}

#pragma endregion

}

/*
void CharActor::InitPhysics()
{
	if (!theWorld.IsPhysicsSetUp())
	{
		sysLog.Log("ERROR: World physics must be initialized before Actor's.");
		return;
	}
	
	b2CircleShape circle;
	b2PolygonShape box;
	b2Shape* shape = NULL;
	if (_shapeType == SHAPETYPE_BOX)
	{
		// The extents is just a vector of the box's half widths. 
		// Box2D is tuned for meters, kilograms, and seconds. (Unless you've changed its units.)
		box.SetAsBox(0.5f*_size.X, 0.5f*_size.Y);
		shape = &box;
	}
	else if (_shapeType == SHAPETYPE_CIRCLE)
	{
		// TODO: handle ellipse?
		circle.m_radius = 0.5f*_size.X;
		shape = &circle;
	}
	else
	{
		sysLog.Log("ERROR: Invalid shape type given.");
		return;
	}
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = _density;
	fixtureDef.friction = _friction;
	fixtureDef.restitution = _restitution;
	
	fixtureDef.filter.groupIndex = _groupIndex;
	fixtureDef.isSensor = _isSensor;
	
	InitShape( shape );
	
	b2BodyDef bd;

	// CHANGED FROM HERE
	//bd.userData = this;
	bd.userData = NULL;
	// CHANGED UNTIL HERE

	bd.position.Set(_position.X, _position.Y);
	bd.angle = MathUtil::ToRadians(_rotation);
	bd.fixedRotation = _fixedRotation;
	
	//=====================================================//
	// CHANGED FROM HERE
	
	if(m_isKinematic)
	{
		bd.type = b2_kinematicBody;
	}
	else
	{
		if (MathUtil::FuzzyEquals(_density, 0.0f))
		{
			bd.type = b2_staticBody;
		}
		else 
		{
			bd.type = b2_dynamicBody;
		}
	}
	
	//  CHANGED UNTIL HERE
	//=====================================================//
	
	_physBody = theWorld.GetPhysicsWorld().CreateBody(&bd);
	_physBody->CreateFixture(&fixtureDef);
	_physBody->SetUserData(this);
	CustomInitPhysics();
}
*/