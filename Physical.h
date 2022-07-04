#pragma once

#include <Windows.h>
#include <vector>

#include "Interfaces.h"

class World;
class Snake;

class Physics
{
public:
    Physics& getInstance();

    bool checkHitCoord(const COORD, const COORD);

    template<typename T>
    void bindPhysicsObject(T* obj)
    {
        _physicsObjects.emplace_back(obj);
    }

private:
    std::vector<IPhysics*> _physicsObjects;

    Physics() {};

    Physics(const Physics&);
    Physics& operator=(const Physics&);
};

