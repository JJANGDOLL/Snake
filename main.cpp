#include <stdio.h>
#include <Windows.h>
#include <chrono>

#pragma comment(lib, "kernel32.lib")

HANDLE hStdout;
HANDLE hStdin;

bool isEnd = false;
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


#define GET_LAST_ERROR printf("%s::%d %d", __FILE__, __LINE__, GetLastError())

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
        SetConsoleCursorPosition(hStdout, pCoord);

        printf("Key event: ");
        printf("0x%08x key released\n", ker.wVirtualKeyCode);
    }

    return true;
}

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

void ElapsedTimer()
{
    COORD tCoord = {0, 0};
    SetConsoleCursorPosition(hStdout, tCoord);

    printf("Time Diff : %10lld\n", std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - begin).count());
    ProcessUserInput();
}


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


    while(!isEnd)
    {
        ElapsedTimer();
        ProcessUserInput();
    }
}

