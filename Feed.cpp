#include "Feed.h"
#include "Utilities.h"
#include "World.h"
#include "Screen.h"

#include <sstream>

Feed::Feed()
    : _shape('X')
{
    
}

void Feed::init()
{
    COORD sPos = _world->startMapCoord();
    _mapSize = _world->MapSize();

    sPos.X += (_mapSize)+(_mapSize >> 1);
    sPos.Y += (_mapSize >> 1);

    _feedCoord = sPos;
}

void Feed::newFeed(World& world)
{
    randomInRange(world.MapSize());
}

void Feed::checkHit()
{
}

void Feed::update()
{
    std::ostringstream stringStream;

    stringStream << _shape;

    _screen->GetCurrentBuffer().AddData(_feedCoord, stringStream.str());
}

void Feed::setWorld(World* world)
{
    _world = world;
}

void Feed::SetScreen(Screen& pscreen)
{
    _screen = &pscreen;
}
