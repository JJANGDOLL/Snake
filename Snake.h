#include <Windows.h>
#include <stdint.h>
#include <deque>
#include "Interfaces.h"

class Screen;
class World;

class Snake: public IUpdate, public IWorld
{
private:
    enum class MoveDir
    {
        Up,
        Down,
        Left,
        Right
    };

    const static char BodyShape;

public:
    Snake()
        : _len(3), _screen(nullptr), _world(nullptr), _moveDir(MoveDir::Right), _tickCount(0), _speedDelay(4), _eatFeedCount(0)
    {};

    void SetScreen(Screen& pScreen);

    void setWorld(World* world);

    void update();

    void init();

    inline void setMoveUp() { _moveDir = MoveDir::Up; };
    inline void setMoveDown() { _moveDir = MoveDir::Down; };
    inline void setMoveLeft() { _moveDir = MoveDir::Left; };
    inline void setMoveRight() { _moveDir = MoveDir::Right; };

    void growUp();

    inline COORD getHeadCoord()
    {
        return _bodies[0];
    }

    inline auto getBodies()
    {
        std::deque<COORD> slice(_bodies.begin() + 1, _bodies.end());
        return slice;
    }

    virtual void listenEvent(ECustomEvents event) override;


    virtual void reset() override;

private:
    uint8_t _len = 3;
    Screen* _screen;
    World* _world;
    MoveDir _moveDir;
    std::deque<COORD> _bodies;
    UINT8 _tickCount;
    UINT8 _eatFeedCount;
    UINT8 _speedDelay;

    void moveSnake();
};