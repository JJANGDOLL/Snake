#pragma once

#include <Windows.h>
#include <string>
#include "Interfaces.h"

class World;
class Screen;

class Feed : public IPhysics, public IUpdate, public IWorld
{
public:
    Feed();

    void init();
    void newFeed(World& world);

    inline COORD getFeedCoord()
    {
        return _feedCoord;
    }

    inline char getShape()
    {
        return _shape;
    }

    virtual void checkHit() override;


    virtual void update() override;


    virtual void setWorld(World* world) override;

    void SetScreen(Screen& pScreen);
private:
    COORD _feedCoord;
    int _mapSize;
    char _shape;
    World* _world;
    Screen* _screen;
};