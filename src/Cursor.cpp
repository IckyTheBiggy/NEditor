#include "Cursor.h"

Cursor::Cursor(int x, int y, int blinkInterval)
{
    this->X = x;
    this->Y = y;
    this->BlinkInterval = blinkInterval;
    this->BlinkTimer = 0;
    this->Visible = true;
}

void Cursor::MoveLeft()
{
    if (X > 0) X--;
}

void Cursor::MoveRight(int maxX)
{
    if (X < maxX) X++;
}

void Cursor::MoveUp()
{
    if (Y > 0) Y--;
}

void Cursor::MoveDown(int maxY)
{
    if (Y < maxY) Y++;
}

void Cursor::Render()
{
    if (Visible)
    {
        int cursorX = X * MeasureText("W", FONT_SIZE) + TEXT_PADDING;
        int cursorY = Y * (FONT_SIZE + 5) + TEXT_PADDING;
        DrawRectangle(cursorX, cursorY, CURSOR_WIDTH, FONT_SIZE, RAYWHITE);
    }
}

void Cursor::UpdateBlink()
{
    BlinkTimer++;

    if (BlinkTimer >= BlinkInterval)
    {
        Visible = !Visible;
        BlinkTimer = 0;
    }
}

int Cursor::GetX() const
{
    return X;
}

int Cursor::GetY() const
{
    return Y;
}

void Cursor::SetX(int newX)
{
    X = newX;
}

void Cursor::SetY(int newY)
{
    Y = newY;
}