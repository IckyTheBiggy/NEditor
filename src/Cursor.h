#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#define FONT_SIZE 20
#define TEXT_PADDING 10
#define CURSOR_WIDTH 2

class Cursor
{   
public:
    Cursor(int x, int y, int blinkInterval, const std::vector<std::string>& textBuffer, const Font& font);

    void MoveLeft();
    void MoveRight(int maxX);
    void MoveUp();
    void MoveDown(int maxY);

    void Render();
    void UpdateBlink();
    void ResetBlink();

    int GetX() const;
    int GetY() const;
    void SetX(int newX);
    void SetY(int newY);

    void SetTextBuffer(std::vector<std::string>& textBuffer);

private:
    int x, startX, currentX, targetX;
    int y, startY, currentY, targetY;
    float lerpPos;

    int blinkInterval;
    int blinkTimer;
    bool visible;

    const std::vector<std::string>& textBuffer;
    const Font& font;

    void UpdatePos();
    float LerpPos();
    float ExpoOut(float t);
};
