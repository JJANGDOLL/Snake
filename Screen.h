#pragma once

#include <Vector>
#include <iostream>
#include <Windows.h>

#pragma comment(lib, "kernel32.lib")

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

    void AddData(const COORD& InPos, const std::string InData)
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
    HANDLE hStdout;

public:
    Screen() {};

    void init(const HANDLE InHandle);

    ScreenBuffer& GetCurrentBuffer();

    void DrawCall();
};