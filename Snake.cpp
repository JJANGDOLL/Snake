#include "Snake.h"
#include "World.h"
#include "Screen.h"
#include <sstream>

void Snake::SetScreen(Screen& pScreen)
{
    _screen = &pScreen;
}

void Snake::setWorld(World* world)
{
    _world = world;
}

void Snake::update()
{
    COORD coord = snakeStartCoord();

    std::ostringstream stringStream;

    stringStream << "A";

    _screen->GetCurrentBuffer().AddData(snakeStartCoord(), stringStream.str());
}

COORD Snake::snakeStartCoord()
{
    COORD mapStartCoord = _world->startMapCoord();
    uint8_t mapSize = _world->MapSize();

    mapStartCoord.X += (mapSize >> 2);
    mapStartCoord.Y += (mapSize >> 2);

    return mapStartCoord;
}

