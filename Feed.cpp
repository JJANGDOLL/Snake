#include "Feed.h"
#include "Utilities.h"
#include "World.h"

Feed::Feed(World* world)
    : _shape('X')
{
    COORD sPos = world->startMapCoord();
    _mapSize = world->MapSize();

    sPos.X += (_mapSize) + (_mapSize >> 1);
    sPos.Y += (_mapSize >> 1);

    _feedCoord = sPos;
}

void Feed::newFeed(World& world)
{
    randomInRange(world.MapSize());
}
