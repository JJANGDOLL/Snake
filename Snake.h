#include <Windows.h>
#include <stdint.h>
#include <deque>
#include "Interfaces.h"

class Screen;
class World;

class Snake: public IUpdate, public IWorld, public IPhysics
{
private:
    enum class MoveDir
    {
        Up,
        Down,
        Left,
        Right
    };

    const static char Body;

public:
    Snake()
        : _len(3), _screen(nullptr), _world(nullptr), _moveDir(MoveDir::Right), _tickCount(0)
    {};

    void SetScreen(Screen& pScreen);

    void setWorld(World* world);

    void update();

    void init();

    inline void setMoveUp() { _moveDir = MoveDir::Up; };
    inline void setMoveDown() { _moveDir = MoveDir::Down; };
    inline void setMoveLeft() { _moveDir = MoveDir::Left; };
    inline void setMoveRight() { _moveDir = MoveDir::Right; };
     

    virtual void checkHit() override;

private:
    uint8_t _len = 3;
    Screen* _screen;
    World* _world;
    MoveDir _moveDir;
    std::deque<COORD> _bodies;
    uint16_t _tickCount;

    void moveSnake();
};