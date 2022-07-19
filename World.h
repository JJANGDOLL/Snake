#pragma once

#include <Windows.h>
#include <cassert>
#include <stdint.h>
#include <chrono>
#include <Vector>
#include <iostream>
#include <map>

#include "Events.h"

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
    T* createUpdateObject()
    {
        T* newObj = new T();
        newObj->setWorld(this);
        _updateObjects.emplace_back(newObj);
        return newObj;
    }

    static World& getInstance(int InSize = 0, Screen* InScreen = nullptr);

    COORD startMapCoord();

    inline uint8_t MapSize()
    {
        return _mapSize;
    }

    inline bool isEnd()
    {
        return _isEnd;
    }

    inline void gameEnd()
    {
        _isEnd = true;
    }

    inline double getPerSecond()
    {
        return _perSecond;
    }

    inline void resetBeginTime()
    {
        _beginTime = std::chrono::steady_clock::now();

    }

    inline void gameStart()
    {
        _bGameStart = true;
    }

    void eventBroadcast();

    inline void addEvent(const ECustomEvents& event)
    {
        _customEvents.push_back(event);
    }

    inline auto getBorderCoord()
    {
        return _borderCoord;
    }

    inline bool isGameStart()
    {
        return _bGameStart;
    }

    void gameOver();
    void printScore();
    void scoreUp();

private:
    uint8_t _mapSize;
    Screen* _screen;
    char _guide;
    double _perSecond;
    std::chrono::steady_clock::time_point _beginTime;
    std::vector<IUpdate*> _updateObjects;
    bool _isEnd = false;
    std::map<COORD, bool> _borderCoord;
    std::vector<ECustomEvents> _customEvents;
    bool _bGameStart = false;
    int _score;

    World(int InSize, Screen* InScreen)
        : _mapSize(InSize)
        , _screen(InScreen)
        , _guide('#')
        , _perSecond((double)1.0 / 8.0)
        , _beginTime(std::chrono::steady_clock::now())
        , _score(0)
    {};

    World(const World&);
    World& operator=(const World&);

    void ElapsedTimer();

    void createMap();
    void renderMap();
    void readyToStart();
};


