#include "Snake.h"
#include "World.h"
#include "Screen.h"
#include "Events.h"
#include <sstream>

const char Snake::BodyShape = 'O';

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
    if(_world->isGameStart())
    {
        std::ostringstream stringStream;

        stringStream << Snake::BodyShape;

        if(_tickCount >= _speedDelay)
        {
            moveSnake();
            _tickCount = 0;
        }

        for(COORD body : _bodies)
        {
            _screen->GetCurrentBuffer().AddData(body, stringStream.str(), 1);
        }

        _tickCount++;
    }
}

void Snake::init()
{
    COORD sPos = _world->startMapCoord();
    uint8_t mapSize = _world->MapSize();

    sPos.X += (mapSize >> 1);
    sPos.Y += (mapSize >> 1);

    _moveDir = MoveDir::Right;

    _bodies.clear();
    _bodies.push_back({sPos.X + 1, sPos.Y});
    _bodies.push_back({sPos.X, sPos.Y});
    _bodies.push_back({sPos.X - 1, sPos.Y});

    _speedDelay = 4;
    _eatFeedCount = 0;

    _len = 3;
}

void Snake::growUp()
{
    COORD tail = _bodies[_len-1];

    _bodies.push_back(tail);
    _len++;
}

void Snake::listenEvent(ECustomEvents event)
{
    switch(event)
    {
        case ECustomEvents::EAT_FEED:
            growUp();
            _world->scoreUp();
            _eatFeedCount++;
            if(_eatFeedCount == 3)
            {
                _speedDelay--;
            }
            if(_eatFeedCount == 6)
            {
                _speedDelay--;
            }
            if(_eatFeedCount == 9)
            {
                _speedDelay--;
            }
            break;
        default:
            break;
    }
}

void Snake::reset()
{
    init();
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
