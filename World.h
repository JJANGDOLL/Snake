#pragma once

#include <Windows.h>
#include <cassert>
#include <stdint.h>
#include <chrono>
#include <Vector>
#include <iostream>
#include <map>

class Screen;
class IUpdate;
class Feed;

class World
{
public:
    static const COORD StartCoord;

public:
    ~World() {};

    void updateAll();

    template<typename T>
    T* createUpdateObject()
    {
        T* newObj = new T();
        newObj->setWorld(this);
        _updateObjects.emplace_back(newObj);
        return newObj;
    }

    static World& getInstance(int InSize = 0, Screen* InScreen = nullptr);

    COORD startMapCoord();

    uint8_t MapSize()
    {
        return _mapSize;
    }

    bool isEnd()
    {
        return _isEnd;
    }

    void gameEnd()
    {
        _isEnd = true;
    }

    double getPerSecond()
    {
        return _perSecond;
    }

    void resetBeginTime()
    {
        _beginTime = std::chrono::steady_clock::now();
    }

private:
    uint8_t _mapSize;
    Screen* _screen;
    char _guide;
    double _perSecond;
    std::chrono::steady_clock::time_point _beginTime;
    std::vector<IUpdate*> _updateObjects;
    bool _isEnd = false;
    Feed* _feed;
    std::map<COORD, bool> _borderCoord;

    World(int InSize, Screen* InScreen)
        : _mapSize(InSize)
        , _screen(InScreen)
        , _guide('#')
        , _perSecond((double)1.0 / 8.0)
        , _beginTime(std::chrono::steady_clock::now())
        , _feed(nullptr)
    {};

    World(const World&);
    World& operator=(const World&);

    void ElapsedTimer();

    void CreateMap();
    void renderMap();
};


