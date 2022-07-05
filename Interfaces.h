#pragma once

#include "Events.h"

class World;

class IWorld
{
public:
    virtual void setWorld(World* world) = 0;
};

class IUpdate
{
public:
    virtual void update() = 0;
    virtual void listenEvent(ECustomEvents event) = 0;
};

// class IPhysicsSubject
// {
// public:
//    virtual void physicsSubjectNotify(const IPhysicsSubject& entity, const ECustomEvents& event) = 0;
// };
// 
// class IPhysicsObserver
// {
// public:
//    virtual void physicsOnNotify(const IPhysicsSubject& entity, ECustomEvents event) = 0;
// };
