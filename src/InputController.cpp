#include "InputController.h"
#include <raylib.h>

struct KeyRepeatInfo
{
	int key;
	float timeHeld;
	bool isRepeating;
};

bool ctrlPressed;
bool shiftPressed;

KeyRepeatInfo keyRepeat = {0, 0.0f, false};

bool IsWordChar(char c) { return std::isalnum(c) || c == '_'; }

void InputController::HandleKeyPress(std::vector<std::string> &textBuffer,
    Cursor &cursor,
    int key)
{
	switch (key)
	{
	case KEY_BACKSPACE:
		if (ctrlPressed)
		{
			int x = cursor.GetX();
			int y = cursor.GetY();

			std::string &line = textBuffer[y];

			if (x > 0)
			{
				int start = x;

				while (start > 0 && !IsWordChar(line[start - 1]))
				{
					start--;
				}

				while (start > 0 && IsWordChar(line[start - 1]))
				{
					start--;
				}

				line.erase(start, x - start);
				cursor.SetX(start);
			}
		}

		else if (cursor.GetX() > 0)
		{
			textBuffer[cursor.GetY()].erase(cursor.GetX() - 1, 1);
			cursor.MoveLeft();
		}

		else if (cursor.GetX() <= 0 && cursor.GetY() > 0)
		{
			std::string currentLine = textBuffer[cursor.GetY()];
			std::string previousLine = textBuffer[cursor.GetY() - 1];
			textBuffer.insert(textBuffer.begin() + cursor.GetY() - 1,
			    previousLine + currentLine);
			textBuffer.erase(textBuffer.begin() + cursor.GetY());
			textBuffer.erase(textBuffer.begin() + cursor.GetY());
			cursor.MoveUp();
			cursor.SetX(previousLine.size());
		}
		break;

	case KEY_ENTER:
	{
		int x = cursor.GetX();
		int y = cursor.GetY();

		std::string &currentLine = textBuffer[y];

		std::string remainingText = currentLine.substr(x);
		currentLine.erase(x);

		textBuffer.insert(textBuffer.begin() + y + 1, remainingText);

		cursor.MoveDown();
		cursor.SetX(0);
	}
	break;

	case KEY_LEFT:
		if (ctrlPressed)
		{
			int x = cursor.GetX();
			int y = cursor.GetY();
			std::string &line = textBuffer[y];

			if (x > 0)
			{
				while (x > 0 && !IsWordChar(line[x - 1]))
				{
					x--;
				}

				while (x > 0 && IsWordChar(line[x - 1]))
				{
					x--;
				}
			}

			cursor.SetX(x);
		}

		else
		{
			cursor.MoveLeft();
		}
		break;

	case KEY_RIGHT:
		if (ctrlPressed)
		{
			int x = cursor.GetX();
			int y = cursor.GetY();
			std::string &line = textBuffer[y];
			int lineLength = line.size();

			if (x < lineLength)
			{
				while (x < lineLength && !IsWordChar(line[x]))
				{
					x++;
				}

				while (x < lineLength && IsWordChar(line[x]))
				{
					x++;
				}
			}

			cursor.SetX(x);
		}

		else
		{
			cursor.MoveRight();
		}
		break;

	case KEY_UP:
		cursor.MoveUp();
		cursor.SetX(
		    std::min(cursor.GetX(), (int)textBuffer[cursor.GetY()].size()));
		break;

	case KEY_DOWN:
		cursor.MoveDown();
		cursor.SetX(
		    std::min(cursor.GetX(), (int)textBuffer[cursor.GetY()].size()));
		break;

	case KEY_HOME:
		if (ctrlPressed)
		{
			cursor.SetY(0);
			cursor.SetX(0);
		}
		cursor.SetX(0);
		break;

	case KEY_END:
		cursor.SetX((int)textBuffer[cursor.GetY()].size());
		break;
	}
}

void InputController::HandleInput(std::vector<std::string> &textBuffer,
    Cursor &cursor,
    TextDocument &textDocument)
{
	int key = GetCharPressed();

	while (key > 0)
	{
		if (key >= 32 && key <= 126)
		{
			std::string &currentLine = textBuffer[cursor.GetY()];

			if (cursor.GetX() <= currentLine.size())
			{
				currentLine.insert(cursor.GetX(), 1, (char)key);
				cursor.MoveRight();
			}
		}

		key = GetCharPressed();
	}

	int keyPressed = GetKeyPressed();
	if (keyPressed != 0)
	{
		keyRepeat.key = keyPressed;
		keyRepeat.timeHeld = 0.0f;
		keyRepeat.isRepeating = false;
		HandleKeyPress(textBuffer, cursor, keyPressed);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL))
		ctrlPressed = true;
	else if (IsKeyReleased(KEY_LEFT_CONTROL))
		ctrlPressed = false;

	if (IsKeyDown(KEY_LEFT_SHIFT))
		shiftPressed = true;
	else if (IsKeyReleased(KEY_LEFT_SHIFT))
		shiftPressed = false;

	if (ctrlPressed)
	{
		if (IsKeyDown(KEY_S))
		{
			textDocument.SaveTextDocument(textBuffer);
		}
	}

	if (IsKeyDown(keyRepeat.key))
	{
		keyRepeat.timeHeld += GetFrameTime();

		if (keyRepeat.timeHeld >= KEY_REPEAT_DELAY)
		{
			if (!keyRepeat.isRepeating)
			{
				keyRepeat.isRepeating = true;
				HandleKeyPress(textBuffer, cursor, keyRepeat.key);
			}

			else if (keyRepeat.timeHeld >= KEY_REPEAT_DELAY + KEY_REPEAT_RATE)
			{
				HandleKeyPress(textBuffer, cursor, keyRepeat.key);
				keyRepeat.timeHeld = KEY_REPEAT_DELAY;
			}
		}
	}

	else
	{
		keyRepeat.key = 0;
		keyRepeat.timeHeld = 0.0f;
		keyRepeat.isRepeating = false;
	}
}