#pragma once

#include <Windows.h>
#include <string>
#include "Interfaces.h"
#include "Events.h"

class World;
class Screen;

class Feed : public IUpdate, public IWorld
{
public:
    Feed();

    void init();

    inline COORD getFeedCoord()
    {
        return _feedCoord;
    }

    inline char getShape()
    {
        return _shape;
    }

    virtual void update() override;
    virtual void setWorld(World* world) override;

    void setScreen(Screen& pScreen);

    void setNewCoord();

//     void addObserver(IPhysicsObserver* observer);
//     void removeObserver(IPhysicsObserver* observer);



//     virtual void physicsSubjectNotify(const IPhysicsSubject& entity, const ECustomEvents& event) override;


    virtual void listenEvent(ECustomEvents event) override;


    virtual void reset() override;

private:
    COORD _feedCoord;
    int _mapSize;
    char _shape;
    World* _world;
    Screen* _screen;
//     IPhysicsObserver* _physicsObserver[10];
    int _numObservers;
};