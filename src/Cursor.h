#pragma once

#include <raylib.h>

#define FONT_SIZE 20
#define TEXT_PADDING 10
#define CURSOR_WIDTH 2

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
    void SetX(int newX);
    void SetY(int newY);

private:
    int X;
    int Y;
    int BlinkInterval;
    int BlinkTimer;
    bool Visible;
};
