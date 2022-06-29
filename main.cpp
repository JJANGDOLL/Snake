#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <conio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

#include "World.h"
#include "Screen.h"
#include "Snake.h"
#include "InputController.h"

#include "Macros.h"
#include "Interfaces.h"

#pragma comment(lib, "kernel32.lib")

HANDLE hStdout;
HANDLE hStdin;

int main(void)
{
    // CMD 기본 설정
    // 마우스 클릭 불가능, 사이즈 재지정 불가능
    // 키보드 입력 가능
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
    screen->init(hStdout);
    World::getInstance(20, screen);

    DWORD term = 0;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    InputController* controller = World::getInstance().addUpdateFactory<InputController>();
    Snake* snake = World::getInstance().addUpdateFactory<Snake>();

    controller->init(hStdin);

    controller->SetScreen(*screen);
    snake->SetScreen(*screen);

    while(!World::getInstance().isEnd())
    {
        start = std::chrono::steady_clock::now();

        World::getInstance().updateAll();

        screen->DrawCall();

        term = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()) + MS_PER_UPDATE;

        Sleep(term);
    }
}

