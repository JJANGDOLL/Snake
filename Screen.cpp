#include "Screen.h"

ScreenBuffer::ScreenBuffer()
{
    for(int i = 0; i < _nRow; i++)
    {
        std::vector<ScreenData> tData;
        for(int j = 0; j < _nCol; j++)
        {
            ScreenData tElement;
            tElement.pos.X = i;
            tElement.pos.Y = j;
            tElement.isWritted = false;
            tElement.priority = 0;

            tData.push_back(tElement);
        }
        _data.push_back(tData);
    }
}

Screen::Screen()
{

}

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
    for(auto& col : GetCurrentBuffer().GetData())
    {
        for(auto& row : col)
        {
            if(row.isWritted)
            {
                SetConsoleCursorPosition(hStdout, row.pos);
                std::cout << row.data;
            }
        }
    }
    screenBuffer[currentIdx].resetData();
    currentIdx++;
    currentIdx %= 2;
}

void ScreenBuffer::AddData(const COORD& InPos, const std::string InData, const UINT8 InPriority)
{
    UINT8 idx = 0;
    for(auto& ch : InData)
    {
        ScreenData& rData = _data[InPos.X + idx][InPos.Y];
        if(rData.isWritted && InPriority < rData.priority)
        {
            continue;
        }

        rData.data = ch;
        rData.isWritted = true;

        idx++;
    }
}

bool ScreenBuffer::operator<(const COORD& rhs) const
{
    return true;
}
