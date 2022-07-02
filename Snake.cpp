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

    if(_tickCount > 20)
    {
        moveSnake();
        _tickCount = 0;
    }

    for(COORD body : _bodies)
    {
        _screen->GetCurrentBuffer().AddData(body, stringStream.str());
    }
}

void Snake::init()
{
    COORD sPos = _world->startMapCoord();
    uint8_t mapSize = _world->MapSize();

    sPos.X += (mapSize >> 1);
    sPos.Y += (mapSize >> 1);

    _bodies.push_back({sPos.X + 1, sPos.Y});
    _bodies.push_back({sPos.X, sPos.Y});
    _bodies.push_back({sPos.X - 1, sPos.Y});
}

void Snake::moveSnake()
{
    COORD head = _bodies[0];

    switch(_moveDir)
    {
        case MoveDir::Up:
            head.Y -= 1;
            break;
        case MoveDir::Down:
            head.Y += 1;
            break;
        case MoveDir::Left:
            head.X -= 1;
            break;
        case MoveDir::Right:
            head.X += 1;
            break;
    }

    _bodies.push_front(head);
    _bodies.pop_back();
}
