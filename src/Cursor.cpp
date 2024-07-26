#include "Cursor.h"
#include "Lerping.h"

Cursor::Cursor(int x, int y, int blinkInterval,
               const std::vector<std::string> &textBuffer, const Font &font)
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

void Cursor::Render()
{
	float t =
	    Lerping::LerpPos(lerpPos, GetFrameTime() / 0.1f, Easing::CubicOut);
	currentX = Lerping::Lerp(startX, targetX, t);
	currentY = Lerping::Lerp(startY, targetY, t);

	if (!visible)
		return;
	DrawRectangle(currentX, currentY, CURSOR_WIDTH, font.baseSize, RAYWHITE);
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
	std::cerr << x << std::endl;
	UpdatePos();
}

void Cursor::SetY(int newY)
{
	y = newY;
	std::cerr << x << std::endl;
	UpdatePos();
}

void Cursor::UpdatePos()
{
	std::string line = textBuffer[y];

	startX = currentX;
	startY = currentY;

	targetX =
	    TEXT_PADDING + 1 +
	    (x > 0 ? MeasureText(line.substr(0, x).c_str(), font.baseSize) : 0);
	targetY = TEXT_PADDING + y * (font.baseSize + font.baseSize / 2);

	lerpPos = 0;
	ResetBlink();
}