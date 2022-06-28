#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <conio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#pragma comment(lib, "kernel32.lib")


HANDLE hStdout;
HANDLE hStdin;

bool isEnd = false;

#define GET_LAST_ERROR printf("%s::%d %d", __FILE__, __LINE__, GetLastError())
#define MS_PER_UPDATE (unsigned long)1.0 / 60.0

class IUpdate
{
public:
    virtual void update() = 0;
};

struct ScreenData
{
    COORD pos;
    std::string data;
};

class ScreenBuffer
{
private:
    std::vector<ScreenData> data;

public:
    ScreenBuffer() {};

    void AddData(COORD& InPos, std::string InData)
    {
        ScreenData t;
        t.pos = InPos;
        t.data = InData;
        data.push_back(t);
    }

    std::vector<ScreenData> GetData()
    {
        return data;
    }

    void Clear()
    {
        data.clear();
    }
};

class Screen
{
private:
    ScreenBuffer screenBuffer[2];
    int currentIdx = 0;

public:
    Screen() {};

    ScreenBuffer& GetCurrentBuffer()
    {
        return screenBuffer[currentIdx];
    }

    void DrawCall()
    {
        for(ScreenData d : GetCurrentBuffer().GetData())
        {
            SetConsoleCursorPosition(hStdout, d.pos);
            std::cout << d.data << std::endl;
        }

        GetCurrentBuffer().Clear();

        currentIdx++;
        currentIdx%=2;
    }
};

class Snake
{


private:
    uint8_t _len = 3;
};

class InputController : public IUpdate
{
public:
    InputController()
        : _screen(nullptr)
    {};

    void SetScreen(Screen& pScreen)
    {
        _screen = &pScreen;
    }

    void update()
    {
        ProcessUserInput();
    }

private:
    Screen* _screen;

    void ProcessUserInput()
    {
        INPUT_RECORD inRecordBuffer[128];
        DWORD numOfRead;
        if(GetNumberOfConsoleInputEvents(hStdin, &numOfRead))
        {
            if(numOfRead > 0)
            {
                if(!ReadConsoleInput(
                    hStdin,
                    inRecordBuffer,
                    128,
                    &numOfRead
                ))
                {
                    GET_LAST_ERROR;
                }

                for(int i = 0; i < numOfRead; i++)
                {
                    switch(inRecordBuffer[i].EventType)
                    {
                        case KEY_EVENT:
                            KeyEventProc(inRecordBuffer[i].Event.KeyEvent);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }

    bool KeyEventProc(KEY_EVENT_RECORD ker)
    {
        if(ker.bKeyDown)
            return false;

        switch(ker.wVirtualKeyCode)
        {
            case VK_ESCAPE:
                isEnd = true;
                break;

            default:
                break;
        }

        if(!ker.bKeyDown)
        {
            COORD pCoord = {0, 1};

            std::ostringstream stringStream;

            stringStream << "Key event: " << ker.wVirtualKeyCode << " key released\n";
            _screen->GetCurrentBuffer().AddData(pCoord, stringStream.str());
        }

        return true;
    }

};

class World
{
public:
    World(int InSize, Screen& InScreen)
        : _size(InSize)
        , _screen(InScreen)
        , _guide('#')
        , _perSecond(1/60)
        , _beginTime(std::chrono::steady_clock::now())
    {};

    void updateAll()
    {
        CreateMap();
        ElapsedTimer();

        for(IUpdate* u : updateObjects)
        {
            u->update();
        }
    }

    template<typename T>
    T* addUpdateFactory()
    {
        T* newObj = new T();
        updateObjects.emplace_back(newObj);
        return newObj;
    }

private:
    int _size;
    Screen& _screen;
    char _guide;
    int _perSecond;
    std::chrono::steady_clock::time_point _beginTime;

    std::vector<IUpdate*> updateObjects;

    void ElapsedTimer()
    {
        COORD tCoord = {0, 0};
        std::ostringstream stringStream;

        stringStream << "Time Elapsed : " << std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - _beginTime).count();

        _screen.GetCurrentBuffer().AddData(tCoord, stringStream.str());
    }

    void CreateMap()
    {
        COORD tCoord = {0, 2};

        std::ostringstream stringStream;

        for(int i = 0; i < _size * 2; i++)
        {
            stringStream << _guide;
        }
        stringStream << "\n";

        for(int i = 0; i < _size - 1; i++)
        {
            stringStream << _guide;
            for(int j = 0; j < (_size * 2) - 2; j++)
            {
                stringStream << " ";
            }
            stringStream << _guide;
            stringStream << "\n";
        }

        for(int i = 0; i < _size * 2; i++)
        {
            stringStream << _guide;
        }
        stringStream << "\n";

        _screen.GetCurrentBuffer().AddData(tCoord, stringStream.str());
    }
};

int main(void)
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if(hStdin == INVALID_HANDLE_VALUE)
    {
        GET_LAST_ERROR;
    }

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hStdout == INVALID_HANDLE_VALUE)
    {
        GET_LAST_ERROR;
    }

    DWORD fwMode = ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;
    if(!SetConsoleMode(hStdin, fwMode))
    {
        GET_LAST_ERROR;
    }

    CONSOLE_CURSOR_INFO cursorInfo = {0,};
    if(!GetConsoleCursorInfo(hStdout, &cursorInfo))
    {
        GET_LAST_ERROR;
    }

    cursorInfo.bVisible = FALSE;
    if(!SetConsoleCursorInfo(hStdout, &cursorInfo))
    {
        GET_LAST_ERROR;
    }

    Screen* screen = new Screen();
    World world(20, *screen);

    DWORD term = 0;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();


    InputController* controller = world.addUpdateFactory<InputController>();

    controller->SetScreen(*screen);

    while(!isEnd)
    {
        start = std::chrono::steady_clock::now();

        world.updateAll();

        screen->DrawCall();

        term = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()) + MS_PER_UPDATE;

        Sleep(term);
    }
}

