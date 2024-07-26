#pragma once

#include "Cursor.h"
#include <cctype>
#include <raylib.h>
#include <string>
#include <vector>

const float KEY_REPEAT_DELAY = 0.5f;
const float KEY_REPEAT_RATE = 0.03f;

class InputController
{
  private:
  public:
	void HandleKeyPress(std::vector<std::string> &textBuffer, Cursor &cursor,
	                    int key);
	void HandleInput(std::vector<std::string> &textBufferm, Cursor &cursor);
};
