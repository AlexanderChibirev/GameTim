#pragma once

#include "cocos_custom.h"
#include "IMapPhysics.h"

class IGameWorld
{
public:
    virtual ~IGameWorld() = default;
    virtual cocos2d::Vec2 GetHeroPosition()const = 0;
    virtual IMapPhysics & GetMap() = 0;
};
