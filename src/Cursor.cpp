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
        DrawRectangle(X * 10, Y * 10, 5, 20, RAYWHITE);
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