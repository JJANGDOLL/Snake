#pragma once

#include <Windows.h>
#include <vector>
#include "Events.h"

#include "Interfaces.h"

class World;
class Snake;

class Physics
{
public:
    static Physics& getInstance();

    bool checkHitCoord(const COORD, const COORD);

//     template<typename T>
//     void bindPhysicsSubject(T* obj)
//     {
//         _physicsObjects.emplace_back(obj);
//     }


private:
//     std::vector<IPhysicsSubject*> _physicsObjects;
    std::vector<ECustomEvents> _customEvents;

    Physics() {};

    Physics(const Physics&);
    Physics& operator=(const Physics&);
};

