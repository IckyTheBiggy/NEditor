#include "Cursor.h"
#include <iostream>
#include <cmath>

Cursor::Cursor(int x, int y, int blinkInterval, const std::vector<std::string>& textBuffer, const Font& font)
    : textBuffer(textBuffer), font(font)
{
    this->startX = this->currentX = 0;
    this->startY = this->currentY = 0;
    this->x = x;
    this->y = y;

    this->blinkInterval = blinkInterval;
    this->blinkTimer = 0;
    this->visible = true;
    
    UpdatePos();
}

void Cursor::MoveLeft()
{
    if (x > 0) SetX(x - 1);
}

void Cursor::MoveRight(int maxX)
{
    if (y < maxX) SetX(x + 1);
}

void Cursor::MoveUp()
{
    if (x > 0) SetY(y - 1);
}

void Cursor::MoveDown(int maxY)
{
    if (y < maxY) SetY(y + 1);
}

void Cursor::Render()
{
    float t = CubicOut(LerpPos());
    currentX = Lerp(startX, targetX, t);
    currentY = Lerp(startY, targetY, t);

    if (!visible) return;
    DrawRectangle(currentX, currentY, CURSOR_WIDTH, font.baseSize, RAYWHITE);
}

void Cursor::UpdateBlink()
{
    if (blinkInterval == 0 || lerpPos < 1) return;
    blinkTimer++;

    if (blinkTimer >= blinkInterval)
    {
        visible = !visible;
        blinkTimer = 0;
    }
}

void Cursor::ResetBlink()
{
    blinkTimer = 0;
    visible = true;
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
    UpdatePos();
}

void Cursor::SetY(int newY)
{
    y = newY;
    UpdatePos();
}

void Cursor::UpdatePos()
{
    std::string line = textBuffer[y];
    
    startX = currentX;
    startY = currentY;

    targetX = TEXT_PADDING + 1 + (targetX > 0 ? MeasureText(line.substr(0, x + 1).c_str(), font.baseSize) : 0);
    targetY = TEXT_PADDING + y * (font.baseSize + font.baseSize / 2);
    
    lerpPos = 0;
    std::cerr << startX << " " << startY << " " << targetX << " " << targetY;
    ResetBlink();
}

float Cursor::LerpPos()
{
    if (lerpPos >= 1) return 1;
    lerpPos += GetFrameTime() / 0.1f;
    lerpPos = lerpPos > 1 ? 1 : lerpPos;
    return lerpPos;
}

float Cursor::ExpoOut(float t)
{
    return t == 1.0f ? 1.0f : 1.0f - std::pow(2, -10 * t);
}

float Cursor::CubicOut(float t)
{
    return 1 - std::pow(1 - t, 3);
}

float Cursor::Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}
