#pragma once

#include <raylib.h>

class Cursor
{   
public:
    Cursor(int x, int y, int blinkInterval);

    void MoveLeft();
    void MoveRight(int maxX);
    void MoveUp();
    void MoveDown(int maxY);

    void Render();
    void UpdateBlink();

    int GetX() const;
    int GetY() const;

private:
    int X;
    int Y;
    int BlinkInterval;
    int BlinkTimer;
    bool Visible;
};
