#include <Windows.h>
#include <stdint.h>
#include "Interfaces.h"

class Screen;
class World;

class Snake: public IUpdate, public IWorld
{
public:
    Snake()
        : _len(3), _screen(nullptr), _world(nullptr)
    {};

    void SetScreen(Screen& pScreen);

    void setWorld(World* world);

    void update();

private:
    uint8_t _len = 3;
    Screen* _screen;
    World* _world;

    COORD snakeStartCoord();
};