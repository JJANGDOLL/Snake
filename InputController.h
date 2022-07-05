
#include "Interfaces.h"
#include <Windows.h>

#pragma comment(lib, "kernel32.lib")

class Screen;
class World;
class Snake;

class InputController: public IUpdate, public IWorld
{
public:
    InputController()
        : _screen(nullptr)
    {};

    void init(HANDLE InHandle, Snake& snake)
    {
        hStdin = InHandle;
        _snake = &snake;
    }

    void SetScreen(Screen& pScreen)
    {
        _screen = &pScreen;
    }

    void setWorld(World* world)
    {
        _world = world;
    }

    void update()
    {
        ProcessUserInput();
    }



    virtual void listenEvent(ECustomEvents event) override;

private:
    Screen* _screen;
    World* _world;
    HANDLE hStdin;
    Snake* _snake;

    void ProcessUserInput();

    bool KeyEventProc(KEY_EVENT_RECORD ker);
};