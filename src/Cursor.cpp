#include "Cursor.h"
#include "Lerping.h"
#include <raylib.h>

Cursor::Cursor(int x,
    int y,
    int blinkInterval,
    const std::vector<std::string> &textBuffer,
    const Font &font)
    : textBuffer(textBuffer), font(font)
{
	this->x = x;
	this->y = y;
	this->startX = this->prevX = this->currentX = this->deltaX = 0;
	this->startY = this->prevY = this->currentY = this->deltaY = 0;

	this->blinkInterval = blinkInterval;
	this->blinkTimer = 0;
	this->visible = true;

	UpdatePos();
}

void Cursor::Render()
{
	float t =
	    Lerping::LerpPos(lerpPos, GetFrameTime() / 0.1f, Easing::CubicOut);
	prevX = currentX;
	prevY = currentY;
	currentX = Lerping::Lerp(startX, targetX, t);
	currentY = Lerping::Lerp(startY, targetY, t);
	deltaX = currentX - prevX;
	deltaY = currentY - prevY;

	if (!visible)
		return;
	DrawCursor();
}

void Cursor::MoveLeft()
{
	if (x > 0)
		SetX(x - 1);
}

void Cursor::MoveRight()
{
	int max = textBuffer[GetY()].size();
	if (x < max)
		SetX(x + 1);
}

void Cursor::MoveUp()
{
	if (y > 0)
		SetY(y - 1);
}

void Cursor::MoveDown()
{
	int max = textBuffer.size() - 1;
	if (y < max)
		SetY(y + 1);
}

void Cursor::ResetBlink()
{
	blinkTimer = 0;
	visible = true;
}

int Cursor::GetX() const { return x; }

int Cursor::GetY() const { return y; }

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

void Cursor::SetScrollOffset(int newOffset)
{
	scrollOffset = newOffset;
}

void Cursor::UpdatePos()
{
	std::string line = textBuffer[y];

	startX = currentX;
	startY = currentY;

	targetX =
	    TEXT_PADDING + 1 +
	    (x > 0 ? MeasureText(line.substr(0, x).c_str(), font.baseSize) : 0);
	targetY = TEXT_PADDING + y * (font.baseSize + (float)font.baseSize / 2) - scrollOffset;

	lerpPos = 0;
	ResetBlink();
}

void Cursor::UpdateBlink()
{
	if (blinkInterval == 0 || lerpPos < 1)
		return;
	blinkTimer++;

	if (blinkTimer >= blinkInterval)
	{
		visible = !visible;
		blinkTimer = 0;
	}
}

void Cursor::DrawCursor()
{
	int w = CURSOR_WIDTH;
	int h = font.baseSize;

	float offsetStrength = 0.25f;
	float offsetPower = 2;
	float scaledOffsetStrength = offsetStrength / sqrt(offsetPower);

	float xOffset = -pow(deltaX, offsetPower) * scaledOffsetStrength;
	float yOffset = pow(deltaY, offsetPower) * scaledOffsetStrength;

	float rightOffset = xOffset > 0 ? xOffset : 0;
	float leftOffset = xOffset < 0 ? xOffset : 0;
	float topOffset = yOffset < 0 ? yOffset : 0;
	float bottomOffset = yOffset > 0 ? yOffset : 0;

	Vector2 tlOffset = {leftOffset, topOffset};
	Vector2 trOffset = {rightOffset, topOffset};
	Vector2 brOffset = {rightOffset, bottomOffset};
	Vector2 blOffset = {leftOffset, bottomOffset};

	Vector2 tl = {(float)currentX + tlOffset.x, (float)currentY + tlOffset.y};
	Vector2 tr = {(float)currentX + trOffset.x + w,
	    (float)currentY + trOffset.y};
	Vector2 br = {(float)currentX + brOffset.x + w,
	    (float)currentY + brOffset.y + h};
	Vector2 bl = {(float)currentX + blOffset.x,
	    (float)currentY + blOffset.y + h};

	DrawTriangle(tl, br, tr, RAYWHITE);
	DrawTriangle(tl, bl, br, RAYWHITE);
}