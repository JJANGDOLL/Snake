#pragma once

#include <Vector>
#include <Map>
#include <iostream>
#include <Windows.h>

#pragma comment(lib, "kernel32.lib")

struct ScreenData
{
    COORD pos;
    bool isWritted;
    std::string data;
    UINT8 priority;
};

class ScreenBuffer
{
private:
    std::vector<std::vector<ScreenData>> _data;
    uint8_t _nRow = 50;
    uint8_t _nCol = 25;

public: 
    ScreenBuffer();

    void AddData(const COORD& InPos, const std::string InData, const UINT8 InPriority);

    std::vector<std::vector<ScreenData>> GetData()
    {
        return _data;
    }

    void Clear()
    {
        _data.clear();
    }

    void resetData()
    {
        for(int i = 0; i < _nRow; i++)
        {
            for(int j = 0; j < _nCol; j++)
            {
                _data[i][j].data = "";
                _data[i][j].isWritted = false;
            }
        }
    }

    bool operator<(const COORD& rhs) const;
};

class Screen
{
private:
    int currentIdx = 0;
    HANDLE hStdout;

    ScreenBuffer screenBuffer[2];
public:
    Screen();

    void init(const HANDLE InHandle);

    ScreenBuffer& GetCurrentBuffer();

    void DrawCall();
};