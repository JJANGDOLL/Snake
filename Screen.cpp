
#include "Screen.h"

void Screen::init(HANDLE InHandle)
{
    hStdout = InHandle;
}

ScreenBuffer& Screen::GetCurrentBuffer()
{
    return screenBuffer[currentIdx];
}

void Screen::DrawCall()
{
    for(ScreenData d : GetCurrentBuffer().GetData())
    {
        SetConsoleCursorPosition(hStdout, d.pos);
        std::cout << d.data << std::endl;
    }

    GetCurrentBuffer().Clear();

    currentIdx++;
    currentIdx %= 2;
}

