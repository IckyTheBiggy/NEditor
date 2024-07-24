#pragma once

#include <raylib.h>
#include <string>
#include <vector>

#define FONT_SIZE 20
#define TEXT_PADDING 10
#define CURSOR_WIDTH 2

class Cursor
{   
public:
    Cursor(int x, int y, std::vector<std::string> textBuffer, int blinkInterval);

    void MoveLeft();
    void MoveRight(int maxX);
    void MoveUp();
    void MoveDown(int maxY);

    void Render(const std::vector<std::string>& textBuffer, const Font& font);
    void UpdateBlink();

    int GetX() const;
    int GetY() const;
    void SetX(int newX);
    void SetY(int newY);

    void SetTextBuffer(std::vector<std::string>& textBuffer);

private:
    int x;
    int y;
    int blinkInterval;
    int blinkTimer;
    bool visible;
    std::vector<std::string> textBuffer;
};
