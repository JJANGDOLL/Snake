#pragma once

#include <Windows.h>
#include <string>

class World;

class Feed
{
public:
    Feed(World* world);

    void newFeed(World& world);

    inline COORD getFeedCoord()
    {
        return _feedCoord;
    }

    inline char getShape()
    {
        return _shape;
    }

private:
    COORD _feedCoord;
    int _mapSize;
    char _shape;
};