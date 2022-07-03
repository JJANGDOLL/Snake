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

