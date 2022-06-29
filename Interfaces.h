#pragma once

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
};
