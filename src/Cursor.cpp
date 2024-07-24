#include "Cursor.h"

Cursor::Cursor(int x, int y, std::vector<std::string> textBuffer, int blinkInterval)
{
    this->x = x;
    this->y = y;
    this->textBuffer = textBuffer;
    this->blinkInterval = blinkInterval;
    this->blinkTimer = 0;
    this->visible = true;
}

void Cursor::MoveLeft()
{
    if (x > 0) x--;
}

void Cursor::MoveRight(int maxX)
{
    if (x < maxX) x++;
}

void Cursor::MoveUp()
{
    if (y > 0) y--;
}

void Cursor::MoveDown(int maxY)
{
    if (y < maxY) y++;
}

void Cursor::Render(const std::vector<std::string>& textBuffer, const Font& font)
{
    if (visible)
    {
        std::string line = textBuffer[y];
        int cursorX = TEXT_PADDING;
        
        for (int i = 0; i < x; i++)
        {
            cursorX += MeasureText(line.substr(i, 1).c_str(), font.baseSize);
        }

        int cursorY = TEXT_PADDING + y * (font.baseSize + font.baseSize / 2);
        DrawRectangle(cursorX, cursorY, CURSOR_WIDTH, font.baseSize, RAYWHITE);
    }
}

void Cursor::UpdateBlink()
{
    blinkTimer++;

    if (blinkTimer >= blinkInterval)
    {
        visible = !visible;
        blinkTimer = 0;
    }
}

int Cursor::GetX() const
{
    return x;
}

int Cursor::GetY() const
{
    return y;
}

void Cursor::SetX(int newX)
{
    x = newX;
}

void Cursor::SetY(int newY)
{
    y = newY;
}

void Cursor::SetTextBuffer(std::vector<std::string>& textBuffer)
{
    this->textBuffer = textBuffer;
}