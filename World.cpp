#include <sstream>
#include "Interfaces.h"
#include "World.h"
#include "Screen.h"

const COORD World::StartCoord = {0, 2};

void World::updateAll()
{
    CreateMap();
    ElapsedTimer();

    for(IUpdate* u : _updateObjects)
    {
        u->update();
    }
}

COORD World::startMapCoord()
{
    return World::StartCoord;
}

void World::ElapsedTimer()
{
    COORD tCoord = {0, 0};
    std::ostringstream stringStream;

    stringStream << "Time Elapsed : " << std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - _beginTime).count();

    _screen->GetCurrentBuffer().AddData(tCoord, stringStream.str());
}

void World::CreateMap()
{
    std::ostringstream stringStream;

    for(int i = 0; i < _mapSize * 2; i++)
    {
        stringStream << _guide;
    }
    stringStream << "\n";

    for(int i = 0; i < _mapSize - 1; i++)
    {
        stringStream << _guide;
        for(int j = 0; j < (_mapSize * 2) - 2; j++)
        {
            stringStream << " ";
        }
        stringStream << _guide;
        stringStream << "\n";
    }

    for(int i = 0; i < _mapSize * 2; i++)
    {
        stringStream << _guide;
    }
    stringStream << "\n";

    _screen->GetCurrentBuffer().AddData({World::StartCoord}, stringStream.str());
}

World& World::getInstance(int InSize /*= 0*/, Screen* InScreen /*= nullptr*/)
{
    static World* _instance;
    if(_instance == nullptr)
    {
        assert((InSize > 0) && (InScreen != nullptr));

        _instance = new World(InSize, InScreen);
    }
    return *_instance;
}
