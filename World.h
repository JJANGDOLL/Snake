#pragma once

#include <Windows.h>
#include <cassert>
#include <stdint.h>
#include <chrono>
#include <Vector>
#include <iostream>

class Screen;
class IUpdate;

class World
{
public:
    static const COORD StartCoord;

public:
    ~World() {};

    void updateAll();

    template<typename T>
    T* addUpdateFactory()
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

private:
    uint8_t _mapSize;
    Screen* _screen;
    char _guide;
    int _perSecond;
    std::chrono::steady_clock::time_point _beginTime;
    std::vector<IUpdate*> _updateObjects;
    bool _isEnd = false;

    World(int InSize, Screen* InScreen)
        : _mapSize(InSize)
        , _screen(InScreen)
        , _guide('#')
        , _perSecond(1 / 60)
        , _beginTime(std::chrono::steady_clock::now())
    {};

    static World* _instance;

    World(const World&);
    World& operator=(const World&);

    void ElapsedTimer();

    void CreateMap();
};


