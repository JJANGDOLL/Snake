#include <sstream>

#include "Interfaces.h"
#include "World.h"
#include "Screen.h"
#include "Feed.h"

bool operator<(const COORD& left, const COORD& right)
{
    if(left.X < right.X)
        return true;
    if(left.X > right.X)
        return false;

    if(left.Y < right.Y)
        return true;
    if(left.Y > right.Y)
        return false;

    return false;
}

const COORD World::StartCoord = {0, 2};

void World::updateAll() 
{
    ElapsedTimer();
    printScore();
    renderMap();
    if(!_bGameStart)
    {
        readyToStart();
    }

    for(IUpdate* u : _updateObjects)
    {
        u->update();
    }
}

COORD World::startMapCoord()
{
    return World::StartCoord;
}

void World::eventBroadcast()
{
    if(_customEvents.size() == 0)
        return;
    for(const auto& cEvent : _customEvents)
    {
        for(const auto& obj : _updateObjects)
        {
            obj->listenEvent(cEvent);
        }
    }

    _customEvents.clear();
}

void World::gameOver()
{
    for(IUpdate* u : _updateObjects)
    {
        u->reset();
    }

    _bGameStart = false;
}

void World::printScore()
{
    if(isGameStart())
    {
        COORD tCoord = {0, 1};
        std::ostringstream stringStream;

        stringStream << "Score : " << _score << "     ";

        _screen->GetCurrentBuffer().AddData(tCoord, stringStream.str(), 1);
    }
}

void World::ElapsedTimer()
{
    if(isGameStart())
    {
        COORD tCoord = {0, 0};
        std::ostringstream stringStream;

        stringStream << "Elapsed Time : " << std::chrono::duration_cast<std::chrono::seconds> (std::chrono::steady_clock::now() - _beginTime).count() << "     ";

        _screen->GetCurrentBuffer().AddData(tCoord, stringStream.str(), 1);
    }
}

void World::createMap()
{
    COORD sPos = startMapCoord();

    for(uint8_t i = 0; i < _mapSize; i++)
    {
        for(uint8_t j = 0; j < _mapSize * 2; j++)
        {
            if(i == 0 || i == _mapSize - 1)
            {
                COORD cPos = sPos;
                cPos.X += j;
                cPos.Y += i;
                _borderCoord[cPos] = true;
            }
            else
            {
                if(j == 0 || j == _mapSize * 2 - 1)
                {
                    COORD cPos = sPos;
                    cPos.X += j;
                    cPos.Y += i;
                    _borderCoord[cPos] = true;
                }
                else
                {
                    COORD cPos = sPos;
                    cPos.X += j;
                    cPos.Y += i;
                    _borderCoord[cPos] = false;
                }
            }
        }
    }
}

void World::renderMap()
{
    for(const auto& cell : _borderCoord)
    {
        std::ostringstream mapGuideStream;
        mapGuideStream << (cell.second ? _guide : ' ');
        _screen->GetCurrentBuffer().AddData(cell.first, mapGuideStream.str(), 1);
    }
}

void World::readyToStart()
{
    COORD sPos = startMapCoord();
    int _mapSize = MapSize();

    std::string notice = "Press Space bar to Start Game";


    sPos.X += (_mapSize) - (notice.length() / 2);
    sPos.Y += (_mapSize >> 1);

    std::ostringstream readyNotice;
    readyNotice << notice;
    _screen->GetCurrentBuffer().AddData(sPos, readyNotice.str(), 2);
}

void World::scoreUp()
{
    _score++;
}

World& World::getInstance(int InSize /*= 0*/, Screen* InScreen /*= nullptr*/)
{
    static World* _instance;
    if(_instance == nullptr)
    {
        assert((InSize > 0) && (InScreen != nullptr));

        _instance = new World(InSize, InScreen);
        _instance->createMap();
    }
    return *_instance;
}
