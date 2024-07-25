#include "InputController.h"

struct KeyRepeatInfo
{
    int key;
    float timeHeld;
    bool isRepeating;
};

KeyRepeatInfo keyRepeat = {0, 0.0f, false};

void InputController::HandleKeyPress(std::vector<std::string>& textBuffer, Cursor& cursor, int key)
{
    switch (key)
    {
        case KEY_BACKSPACE:
            if (cursor.GetX() > 0)
            {
                textBuffer[cursor.GetY()].erase(cursor.GetX() - 1, 1);
                cursor.MoveLeft();
            }
        break;

        case KEY_ENTER:
            textBuffer.insert(textBuffer.begin() + cursor.GetY() + 1, "");
            cursor.MoveDown();
            cursor.SetX(0);
        break;

        case KEY_LEFT:
            cursor.MoveLeft();
        break;

        case KEY_RIGHT:
            cursor.MoveRight();
        break;

        case KEY_UP:
            cursor.MoveUp();
            cursor.SetX(std::min(cursor.GetX(), (int)textBuffer[cursor.GetY()].size()));
        break;

        case KEY_DOWN:
            cursor.MoveDown();
            cursor.SetX(std::min(cursor.GetX(), (int)textBuffer[cursor.GetY()].size()));
        break;
    }
}

void InputController::HandleInput(std::vector<std::string>& textBuffer, Cursor& cursor)
{
    int key = GetCharPressed();

    while (key > 0)
    {
        if (key >= 32 && key <= 126)
        {
            std::string& currentLine = textBuffer[cursor.GetY()];

            if (cursor.GetX() <= currentLine.size())
            {
                currentLine.insert(cursor.GetX(), 1, (char)key);
                cursor.MoveRight();
            }
        }

        key = GetCharPressed();
    }

    int keyPressed = GetKeyPressed();
    if (keyPressed != 0)
    {
        keyRepeat.key = keyPressed;
        keyRepeat.timeHeld = 0.0f;
        keyRepeat.isRepeating = false;
        HandleKeyPress(textBuffer, cursor, keyPressed);
    }

    if (IsKeyDown(keyRepeat.key))
    {
        keyRepeat.timeHeld += GetFrameTime();

        if (keyRepeat.timeHeld >= KEY_REPEAT_DELAY)
        {
            if (!keyRepeat.isRepeating)
            {
                keyRepeat.isRepeating = true;
                HandleKeyPress(textBuffer, cursor, keyRepeat.key);
            }

            else if (keyRepeat.timeHeld >= KEY_REPEAT_DELAY + KEY_REPEAT_RATE)
            {
                HandleKeyPress(textBuffer, cursor, keyRepeat.key);
                keyRepeat.timeHeld = KEY_REPEAT_DELAY;
            }
        }
    }

    else
    {
        keyRepeat.key = 0;
        keyRepeat.timeHeld = 0.0f;
        keyRepeat.isRepeating = false;
    }
}
