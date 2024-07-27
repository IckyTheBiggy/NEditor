#pragma once

#include "Config.h"
#include "Cursor.h"
#include "InputController.h"
#include "TextDocument.h"
#include "toml.hpp"
#include <raylib.h>
#include <string>
#include <vector>

class Editor
{
  public:
	void Run();
	void UpdateScroll(const Cursor &Cursor, const Font &font);

  private:
    int scrollOffset = 0;
};
