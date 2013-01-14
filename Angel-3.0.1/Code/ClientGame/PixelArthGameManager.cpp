#include "stdafx.h"
#include "PixelArthGameManager.h"
#include <map>

#if !ANGEL_MOBILE
    #include "WorldMap/PixelArthScreenCharTest.h"
    #include "WorldMap/Screen2.h"
    #include "WorldMap/Screen3.h"
    #include "WorldMap/Screen4.h"

#endif

//#include "PixelArthScreenMobileSimulator.h"

PixelArthScreen::PixelArthScreen() {}

void PixelArthScreen::Start(){}

void PixelArthScreen::Stop()
{
    std::vector<Renderable*>::iterator it = _objects.begin();
    while(_objects.end() != it)
    {
        // we're pre-destroying physics bodies here because it 
        //  can mess with the pathfinding regeneration.
        PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
        if (pa != NULL)
        {
            if (pa->GetBody() != NULL)
            {
                pa->GetBody()->SetUserData(NULL);
                theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
                pa->ResetBody();
            }
        }
        (*it)->Destroy();
        it++;
    }
    _objects.clear();

    m_arth = NULL;

    /*if (m_arth != NULL)
    {
	    if (m_arth->GetBody() != NULL)
	    {
		    m_arth->GetBody()->SetUserData(NULL);
		    theWorld.GetPhysicsWorld().DestroyBody(m_arth->GetBody());
		    m_arth->ResetBody();
	    }
    }
    m_arth->Destroy();*/

    // clear bitmasks
    std::map<String, Bitmask*>::iterator it2 = m_bitmaskmap.begin();
    while(m_bitmaskmap.end() != it2)
    {
        delete (*it2).second;
        //it2 = (*it2).second.erase(it2);
        ++it2;
    }
    m_bitmaskmap.clear();
}

void PixelArthScreen::Update(float dt)
{
    //for (b2Contact* c = theWorld.GetPhysicsWorld().GetContactList(); c; c = c->GetNext())
    //{
    //    // process c
    //    //c->GetFixtureA()->GetBody()->GetUserData();
    //    PhysicsActor* pa = static_cast<PhysicsActor*> (c->GetFixtureA()->GetBody()->GetUserData());
    //    
    //    CollidingActor* ca = dynamic_cast<CollidingActor*>(pa);
    //    if (ca != NULL)
    //    {
    //        std::cout << "Body userData: " << ca->GetMask()->getPath() << std::endl;
    //    }
    //}

    /*std::vector<Renderable*>::iterator it = _objects.begin();
    while(_objects.end() != it)
    {
        CollidingActor* pa = dynamic_cast<CollidingActor*> (*it);
        if (pa != NULL)
        {
            if (pa->GetBody() != NULL)
            {
                pa->GetBody()->SetUserData(NULL);
                theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
                pa->ResetBody();
            }
        }
        (*it)->Destroy();
        it++;
    }
    _objects.clear();*/

    std::vector<Renderable*>::iterator it = _objects.begin();
    while(_objects.end() != it)
    {
        // TODO: GroundActor and ButtonActor need to be derived from the same class e.g. EnvironmentActor
        GroundActor* ga = dynamic_cast<GroundActor*> (*it);
        if(ga == NULL)
        {
            ButtonActor* ba = dynamic_cast<ButtonActor*> (*it);
            if(ba == NULL)
            {
                CollidingActor* pa = dynamic_cast<CollidingActor*> (*it);

                if (pa != NULL)
                {
                    //std::cout << "destroyed? " << pa->IsDestroyed() << std::endl;
                    if(!pa->IsDestroyed()){ // not neccessary?
                        //std::cout << "SetLayer: " << -MathUtil::WorldUnitsToPixels(pa->GetPosition().Y-(pa->GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2) << std::endl;
                        pa->SetLayer(-MathUtil::WorldUnitsToPixels(pa->GetPosition().Y-(pa->GetSize().Y/2))+MathUtil::WorldUnitsToPixels(MathUtil::GetWorldDimensions().Y/2));
                        // TEST: DEBUG: TODO: WTF
                        //pa->SetLayer(10);
                        //pa->SetLayer(20);
                    }
                }
            }
        }
        it++;
    }

    //std::cout << "pos: " << (m_arth->GetPosition()+(m_arth->GetSize()/2)).X << " bBox: " << m_arth->GetBoundingBox().Max.X << " right: " << MathUtil::GetWorldDimensions().X/2 << std::endl;
    if(m_arth->GetBoundingBox().Max.X >= (MathUtil::GetWorldDimensions().X/2))
    {
        thePixelArthGame.MoveForwards();
    }
    if(m_arth->GetBoundingBox().Min.X <= -(MathUtil::GetWorldDimensions().X/2))
    {
        thePixelArthGame.MoveBackwards();
    }
}

void PixelArthScreen::Render() {}

Bitmask * const PixelArthScreen::GetBitmask(const String& path)
{
    if ( m_bitmaskmap.find(path) == m_bitmaskmap.end() ) {
        // not found
        Bitmask* mask = new Bitmask(path);
        m_bitmaskmap.insert(make_pair(path,mask));
    }
    return m_bitmaskmap.at(path);
}


PixelArthGameManager* PixelArthGameManager::s_PixelArthGameManager = NULL;

PixelArthGameManager::PixelArthGameManager()
{	
    //subscribe to messages
    theSwitchboard.SubscribeTo(this, "MoveForwards");
    theSwitchboard.SubscribeTo(this, "MoveBackwards");
    theSwitchboard.SubscribeTo(this, "Dead");
	
    m_collHandler = new CollisionHandler();	
	
    #if ANGEL_MOBILE
        //_screens.push_back(new PixelArthScreenMobileSimulator());				// 0
    #else
        //_screens.push_back(new PixelArthScreenCharTest());
        _screens.push_back(new Screen2());
        _screens.push_back(new Screen3());
        _screens.push_back(new Screen4());
    #endif
	
    unsigned int startingIndex = 0;
    if (_screens.size() > startingIndex)
    {
        theWorld.Add(_screens[startingIndex]);
        _screens[startingIndex]->Start();
        _current = startingIndex;
        //theSwitchboard.SubscribeTo(this, "CollisionStartWith"+GetCurrentScreen()->GetHero()->GetName());
        //theSwitchboard.SubscribeTo(this, "CollisionEndWith"+GetCurrentScreen()->GetHero()->GetName());
    }
    else
    {
        _current = -1;
    }
	
    // We must set the sound callback method.  Although, I'm wondering if we should 
    // allow them to not specify it if they don't need the functionality.
    theSound.SetSoundCallback(this, &GameManager::SoundEnded);
	
    sample = theSound.LoadSample("Resources/Sounds/click.ogg", false /*no stream*/);
}

PixelArthGameManager::~PixelArthGameManager()
{
    delete m_collHandler;
}

PixelArthGameManager& PixelArthGameManager::GetInstance()
{
    if (s_PixelArthGameManager == NULL)
    {
        s_PixelArthGameManager = new PixelArthGameManager();
    }
    return *s_PixelArthGameManager;
}

PixelArthScreen* PixelArthGameManager::GetCurrentScreen()
{
    return _screens[_current];
}

void PixelArthGameManager::Update(float dt)
{
    GameManager::Update(dt);

    //TODODODODOODODODODO!!!!!

    //collidingActor::SetColliding() checks the contactlist

    //manager stores std::vector with all collidingactors
    //on CollisionStartWith: push_back the b2contact from the message
    //in the manager::Update: checkCollisions every frame
    //on CollisionEndWith: check contactlist of actors if they don't contain any CollidingActors pop actor from std::vector?

    b2Contact* contactlist = theWorld.GetPhysicsWorld().GetContactList();
    
    while(contactlist != NULL)
    {
        if((contactlist->GetFixtureA()->GetBody()->GetUserData() == contactlist->GetFixtureB()->GetBody()->GetUserData()))
        {
            std::cout << "WTF" << (contactlist->GetFixtureA()->GetBody()->GetUserData()) << std::endl;
        }
        if(!(contactlist->GetFixtureA()->GetBody()->GetUserData() == contactlist->GetFixtureB()->GetBody()->GetUserData()))
        {
            PhysicsActor *pa = static_cast<PhysicsActor*>(contactlist->GetFixtureA()->GetBody()->GetUserData());
            CollidingActor *ca = dynamic_cast<CollidingActor*>(pa);

            if(ca != NULL)
            {
                PhysicsActor *pb = static_cast<PhysicsActor*>(contactlist->GetFixtureB()->GetBody()->GetUserData());
                CollidingActor *cb = dynamic_cast<CollidingActor*>(pb);

                if (ca != NULL && cb != NULL)
                {
                    //std::cout << ca->GetName() << " collides with " << cb->GetName() << std::endl;
                    /// check with next position of the actors...implement getNextPosition() ?
                    CollFlags cf;
                
                    //std::cout << cf.none << std::endl;

                    cf = m_collHandler->checkCollisions(ca->GetPosition()/*-(ca->GetSize()/2)*//*+Vector2(ca->GetBody()->GetLinearVelocity().x, ca->GetBody()->GetLinearVelocity().y)*/ , *(ca->GetMask()), cb->GetPosition()/*-(cb->GetSize()/2)*//*+Vector2(ca->GetBody()->GetLinearVelocity().x, ca->GetBody()->GetLinearVelocity().y)*/, *(cb->GetMask()));
                
                    //std::cout << "after coll call: " << cf.wall << std::endl;
                
                    ca->Collide(cf);
                    //std::cout << cf.none << std::endl;

                    cf = m_collHandler->checkCollisions(cb->GetPosition()/*+Vector2(ca->GetBody()->GetLinearVelocity().x, ca->GetBody()->GetLinearVelocity().y)*/ , *(cb->GetMask()), ca->GetPosition()/*+Vector2(ca->GetBody()->GetLinearVelocity().x, ca->GetBody()->GetLinearVelocity().y)*/, *(ca->GetMask()));
                    cb->Collide(cf);
                }
            }
        }
        contactlist = contactlist->GetNext();
    }
}

void PixelArthGameManager::ReceiveMessage(Message* message)
{
    if (message->GetMessageName() == "MoveForwards")
    {
        MoveForwards();
    }
    else if (message->GetMessageName() == "MoveBackwards")
    {
        MoveBackwards();
    }
    else if (message->GetMessageName() == "Dead")
    {
        _screens[_current]->Stop();
        theWorld.Remove(_screens[_current]);
        _screens[_current]->Start();
        theWorld.Add(_screens[_current]);
    }

    /*if (message->GetMessageName() == "CollisionStartWith"+ _screens[_current]->GetHero()->GetName())
    {
        //collidingActor::SetColliding() checks the contactlist

        //manager stores std::vector with all collidingactors
        //on CollisionStartWith: push_back the b2contact from the message
        //in the manager::Update: checkCollisions every frame
        //on CollisionEndWith: check contactlist of actors if they don't contain any CollidingActors pop actor from std::vector?
        TypedMessage<b2Contact*>* coll = dynamic_cast<TypedMessage<b2Contact*>*>(message);

        //TypedMessage<b2Contact*>* coll = new TypedMessage<b2Contact*>(pa1Message, contact, pa2);
        b2Contact* b2c = coll->GetValue();
        
        
        
        PhysicsActor *pa = static_cast<PhysicsActor*>(b2c->GetFixtureA()->GetBody()->GetUserData());
        PhysicsActor *pb = static_cast<PhysicsActor*>(b2c->GetFixtureB()->GetBody()->GetUserData());
        
        CollidingActor *ca = dynamic_cast<CollidingActor*>(pa);
        CollidingActor *cb = dynamic_cast<CollidingActor*>(pb);

        if (ca != NULL && cb != NULL)
        {
            std::cout << "char contacts with " << ca->GetName() << std::endl;
            /// check with next position of the actors...implement getNextPosition() ?
            CollFlags cf = m_collHandler->checkCollisions(ca->GetPosition()+Vector2(ca->GetBody()->GetLinearVelocity().x, ca->GetBody()->GetLinearVelocity().y) , *(ca->GetMask()), cb->GetPosition()+Vector2(ca->GetBody()->GetLinearVelocity().x, ca->GetBody()->GetLinearVelocity().y), *(cb->GetMask()));
            ca->SetCollFlags(cf);
            cb->SetCollFlags(cf);
        }
    }*/
}

void PixelArthGameManager::MoveForwards()
{
    if ((_current >= 0) && (_current < (int)_screens.size() - 1))
    {
        //theSwitchboard.UnsubscribeFrom(this, "CollisionStartWith"+GetCurrentScreen()->GetHero()->GetName());
        //theSwitchboard.UnsubscribeFrom(this, "CollisionEndWith"+GetCurrentScreen()->GetHero()->GetName());
        _screens[_current]->Stop();
        theWorld.Remove(_screens[_current]);
        _screens[++_current]->Start();
        theWorld.Add(_screens[_current]);
        //theSwitchboard.SubscribeTo(this, "CollisionStartWith"+GetCurrentScreen()->GetHero()->GetName());
        //theSwitchboard.SubscribeTo(this, "CollisionEndWith"+GetCurrentScreen()->GetHero()->GetName());
		
        //if (sample)
        //    theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
    }
}

void PixelArthGameManager::MoveBackwards()
{
    if (_current > 0)
    {
        _screens[_current]->Stop();
        theWorld.Remove(_screens[_current]);
        _screens[--_current]->Start();
        theWorld.Add(_screens[_current]);
		
        //if (sample)
        //    theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
    }
}

void PixelArthGameManager::Render()
{
    //glColor3f(0.5f, 0.5f, 0.5f);
    //char* infoString = "";
    //int xOffset = 0;
    //if (_current == 0)
    //{
    //    infoString = "[A/Space]: Next";
    //    xOffset = 887;
    //}
    //else if (_current == _screens.size() - 1)
    //{
    //    infoString = "[Back/Minus]: Previous";
    //    xOffset = 824;
    //}
    //else
    //{
    //    infoString = "[A/Space]: Next [Back/Minus]: Previous";
    //    xOffset = 680;
    //}
    //DrawGameText(infoString, "ConsoleSmall", xOffset, 563);	//763
}

void PixelArthGameManager::SoundEnded(AngelSoundHandle sound)
{	
    // Detect sounds that have ended here.
}