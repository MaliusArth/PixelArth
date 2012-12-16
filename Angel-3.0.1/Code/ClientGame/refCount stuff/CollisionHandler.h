#pragma once
#include "Physics/Bitmask.h"
#include "ReferenceToObj.h"
#include <map>

/// <summary></summary>
struct CollFlags
{
    CollFlags(void)
    {
        floor = 0;
        wall = 0;
        none = 0;
    }
    unsigned int floor : 1;
    unsigned int wall : 1;
    unsigned int none : 1;
};

/// <summary></summary>
class CollisionHandler{
public:
	CollisionHandler();
    ReferenceToObj<Bitmask> GetBitmask(const String& path);
	CollFlags checkCollisions(const Vector2&,const Bitmask&, const Vector2&, const Bitmask&) const;
private:
    std::map<String, ReferenceToObj<Bitmask>> m_bitmaskmap;
};