#include "Snake.h"
#include "World.h"
#include "Screen.h"
#include <sstream>

const char Snake::Body = 'O';

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
    std::ostringstream stringStream;

    stringStream << Snake::Body;
    _tickCount++;

    if(_tickCount > 30)
    {
        moveSnake();
        _tickCount = 0;
    }

    _screen->GetCurrentBuffer().AddData(_currCoord, stringStream.str());
}

void Snake::init()
{
    _currCoord = _world->startMapCoord();
    uint8_t mapSize = _world->MapSize();

    _currCoord.X += (mapSize >> 1);
    _currCoord.Y += (mapSize >> 1);
}

void Snake::moveSnake()
{
    switch(_moveDir)
    {
        case MoveDir::Up:
            _currCoord.Y -= 1;
            break;
        case MoveDir::Down:
            _currCoord.Y += 1;
            break;
        case MoveDir::Left:
            _currCoord.X -= 1;
            break;
        case MoveDir::Right:
            _currCoord.X += 1;
            break;
    }
}
