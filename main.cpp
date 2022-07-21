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
#include "Physical.h"
#include "Feed.h"

#include "Macros.h"
#include "Interfaces.h"
#include "Utilities.h"

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
    World::getInstance(20, screen);

    double term = 0;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    InputController* controller = World::getInstance().createUpdateObject<InputController>();
    Snake* snake = World::getInstance().createUpdateObject<Snake>();
    Feed* feed = World::getInstance().createUpdateObject<Feed>();

//     Physics::getInstance().bindPhysicsSubject(feed);

    screen->init(hStdout);
    controller->init(hStdin, *snake);
    snake->init();
    feed->init();

    controller->SetScreen(*screen);
    snake->SetScreen(*screen);
    feed->setScreen(*screen);

    while(!World::getInstance().isEnd())
    {
        start = std::chrono::steady_clock::now();

        World::getInstance().updateAll();

        screen->DrawCall();

        if(checkSnakeIsEat(snake->getHeadCoord(), feed->getFeedCoord()))
        {
            World::getInstance().addEvent(ECustomEvents::EAT_FEED);
        }

        for(const auto& border : World::getInstance().getBorderCoord())
        {
            if(border.second == true)
            {
                if(checkSnakeHitBorder(snake->getHeadCoord(), border.first))
                {
                    World::getInstance().gameOver();
                }
            }
        }

        for(const auto& body : snake->getBodies())
        {
            if(checkSnakeHitBody(snake->getHeadCoord(), body))
            {
                World::getInstance().gameOver();
            } 
        }

        for(const auto& body : snake->getBodies())
        {
            if(checkSnakeHitBody(feed->getFeedCoord(), body))
            {
                feed->setNewCoord();
            }
        }

        World::getInstance().eventBroadcast();

        std::chrono::duration<double> elapsedTime = std::chrono::steady_clock::now() - start;
        term = (World::getInstance().getPerSecond() - elapsedTime.count());
        if(term > 0)
            Sleep(int(term * 1000));
    }
}

