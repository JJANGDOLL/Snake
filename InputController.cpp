#include "InputController.h"
#include "Macros.h"
#include "Screen.h"
#include "World.h"
#include "Snake.h"
#include <sstream>

void InputController::ProcessUserInput()
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

            for(DWORD i = 0; i < numOfRead; i++)
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

bool InputController::KeyEventProc(KEY_EVENT_RECORD ker)
{
    if(ker.bKeyDown)
        return false;

    switch(ker.wVirtualKeyCode)
    {
        case VK_ESCAPE:
            _world->gameEnd();
            break;

        default:
            break;
    }

    if(!ker.bKeyDown)
    {
        //COORD pCoord = {0, 1};

        //std::ostringstream stringStream;

        //stringStream << "Key event: " << ker.wVirtualKeyCode << " key released\n";
        //_screen->GetCurrentBuffer().AddData(pCoord, stringStream.str());

        switch(ker.wVirtualKeyCode)
        {
            case VK_UP:
                _snake->setMoveUp();
                break;
            case VK_DOWN:
                _snake->setMoveDown();
                break;
            case VK_LEFT:
                _snake->setMoveLeft();
                break;
            case VK_RIGHT:
                _snake->setMoveRight();
                break;
            case VK_SPACE:
                _world->resetBeginTime();
                break;
            default:
                break;
        }
    }

    return true;
}

