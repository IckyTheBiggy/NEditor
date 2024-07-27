#include "Editor.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const std::string textFilePath = "../test.txt";
std::vector<std::string> textBuffer;

void DrawTextBuffer(std::vector<std::string> textBuffer, const Font &font, int scrollOffset)
{
	for (int i = 0; i < textBuffer.size(); i++)
	{
		int y = TEXT_PADDING + i * (font.baseSize + font.baseSize / 2) - scrollOffset;

		if (y >= -font.baseSize && y < SCREEN_HEIGHT)
		{
			DrawText(textBuffer[i].c_str(),
			    TEXT_PADDING,
			    y,
			    font.baseSize,
			    RAYWHITE);
		}
	}
}

void Editor::UpdateScroll(const Cursor& cursor, const Font &font)
{
	int cursorY = cursor.GetY() * (font.baseSize + font.baseSize / 2);
	int viewportHeight = SCREEN_HEIGHT - 2 * TEXT_PADDING;

	if (cursorY - scrollOffset > viewportHeight)
	{
		scrollOffset = cursorY - viewportHeight;
	}

	else if (cursorY - scrollOffset < TEXT_PADDING)
	{
		scrollOffset = cursorY - TEXT_PADDING;
	}

	scrollOffset = std::max(0, scrollOffset);
}

void Editor::Run()
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");

	Config Config;
	TextDocument textDocument(textFilePath);

	SetTargetFPS(Config.GetInt("fps", 120));
	textDocument.OpenTextDocument(textBuffer);

	Font font = GetFontDefault();
	font.baseSize = 20;
	InputController inputController;
	Cursor cursor(0, 0, 30, textBuffer, font);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLANK);

		inputController.HandleInput(textBuffer, cursor, textDocument);
		cursor.UpdateBlink();

		UpdateScroll(cursor, font);
		cursor.SetScrollOffset(scrollOffset);
		cursor.UpdatePos();

		DrawTextBuffer(textBuffer, font, scrollOffset);

		cursor.Render();

		EndDrawing();
	}

	CloseWindow();
}
