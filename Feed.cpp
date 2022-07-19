#include "Feed.h"
#include "Utilities.h"
#include "World.h"
#include "Screen.h"

#include <sstream>
#include "Events.h"

Feed::Feed()
    : _shape('X'), _numObservers(0)
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

void Feed::update()
{
    if(_world->isGameStart())
    {
        std::ostringstream stringStream;

        stringStream << _shape;

        _screen->GetCurrentBuffer().AddData(_feedCoord, stringStream.str(), 1);
    }
}

void Feed::setWorld(World* world)
{
    _world = world;
}

void Feed::setScreen(Screen& pscreen)
{
    _screen = &pscreen;
}


void Feed::setNewCoord()
{
    COORD sPos = _world->startMapCoord();

    sPos.X += randomInRange(_mapSize * 2 - 3) + 1;
    sPos.Y += randomInRange(_mapSize - 3) + 1;

    _feedCoord = sPos;
}

// void Feed::addObserver(IPhysicsObserver* observer)
// {
//     _physicsObserver[_numObservers] = observer;
// }
// 
// void Feed::removeObserver(IPhysicsObserver* observer)
// {
//     for(int i = 0; i < 10; i++)
//     {
//         if(_physicsObserver[i] == observer)
//         {
//             for(int j = i; j < _numObservers; j++)
//             {
//                 _physicsObserver[j] = _physicsObserver[j + 1];
//             }
//             _numObservers--;
//         }
//     }
// }

// void Feed::physicsSubjectNotify(const IPhysicsSubject& entity, const ECustomEvents& event)
// {
//     for(int i = 0; i < _numObservers; i++)
//     {
//         _physicsObserver[i]->physicsOnNotify(*this, ECustomEvents::EAT_FEED);
//     }
// }

void Feed::listenEvent(ECustomEvents event)
{
    switch(event)
    {
        case ECustomEvents::EAT_FEED:
            setNewCoord();
            break;
        default:
            break;
    }
}

void Feed::reset()
{
    init();
}

