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
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

#define GET_LAST_ERROR printf("%s::%d %d", __FILE__, __LINE__, GetLastError())
#define MAP_SIZE 15

class IUpdate
{
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
    InputController(Screen& screen)
        : _screen(screen)
    {}

    void update()
    {
        ProcessUserInput();
    }

private:
    Screen& _screen;

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
            _screen.GetCurrentBuffer().AddData(pCoord, stringStream.str());
        }

        return true;
    }

};

void ElapsedTimer()
{
    COORD tCoord = {0, 0};
    SetConsoleCursorPosition(hStdout, tCoord);

    printf("Time Diff : %10lld\n", std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - begin).count());
}

class World : public IUpdate
{
public:
    World(int InSize, Screen& InScreen)
        : _size(InSize)
        , _screen(InScreen)
    {};

    void update()
    {
        CreateMap(_size);
    }

private:
    int _size;
    Screen& _screen;

    void CreateMap(int size)
    {
        COORD tCoord = {0, 2};

        std::ostringstream stringStream;
        SetConsoleCursorPosition(hStdout, tCoord);

        for(int i = 0; i < size; i++)
        {
            stringStream << "#";
        }
        stringStream << "\n";

        for(int i = 0; i < size - 1; i++)
        {
            stringStream << "#";
            for(int j = 0; j < size - 2; j++)
            {
                stringStream << " ";
            }
            stringStream << "#";
            stringStream << "\n";
        }

        for(int i = 0; i < size; i++)
        {
            stringStream << "#";
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

    std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();

    Screen screen;

    InputController userInput(screen);
    World world(MAP_SIZE, screen);

    while(!isEnd)
    {
        ElapsedTimer();

        userInput.update();
        world.update();
        screen.DrawCall();
    }
}

