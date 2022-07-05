#include "Physical.h"

Physics& Physics::getInstance()
{
    static Physics* _instance;
    if(_instance == nullptr)
    {
        _instance = new Physics();
    }
    return *_instance;
}

bool Physics::checkHitCoord(const COORD lhs, const COORD rhs)
{
    if(lhs.X == rhs.X && lhs.Y == rhs.Y)
        return true;
    return false;
}


