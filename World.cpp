#include <sstream>
#include "Interfaces.h"
#include "World.h"
#include "Screen.h"
#include "Feed.h"

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

    stringStream << "Score : " << std::chrono::duration_cast<std::chrono::seconds> (std::chrono::steady_clock::now() - _beginTime).count();

    _screen->GetCurrentBuffer().AddData(tCoord, stringStream.str());
}

void World::CreateMap()
{
    std::ostringstream mapGuideStream;

    for(int i = 0; i < _mapSize * 2; i++)
    {
        mapGuideStream << _guide;
    }
    mapGuideStream << "\n";

    for(int i = 0; i < _mapSize - 1; i++)
    {
        mapGuideStream << _guide;
        for(int j = 0; j < (_mapSize * 2) - 2; j++)
        {
            mapGuideStream << " ";
        }
        mapGuideStream << _guide;
        mapGuideStream << "\n";
    }

    for(int i = 0; i < _mapSize * 2; i++)
    {
        mapGuideStream << _guide;
    }
    mapGuideStream << "\n";

    _screen->GetCurrentBuffer().AddData(World::StartCoord, mapGuideStream.str());


    std::ostringstream feedStream;
    feedStream << _feed->getShape();

    _screen->GetCurrentBuffer().AddData(_feed->getFeedCoord(), feedStream.str());
}

World& World::getInstance(int InSize /*= 0*/, Screen* InScreen /*= nullptr*/)
{
    static World* _instance;
    if(_instance == nullptr)
    {
        assert((InSize > 0) && (InScreen != nullptr));

        _instance = new World(InSize, InScreen);
        _instance->_feed = new Feed(_instance);
    }
    return *_instance;
}
