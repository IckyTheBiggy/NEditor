#include "Editor.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const std::string textFilePath = "../test.txt";
std::vector<std::string> TextBuffer = {""};

void DrawTextBuffer(const Font &font)
{
	for (int i = 0; i < TextBuffer.size(); i++)
	{
		DrawText(TextBuffer[i].c_str(), TEXT_PADDING,
		         TEXT_PADDING + i * (font.baseSize + font.baseSize / 2),
		         font.baseSize, RAYWHITE);
	}
}

void Editor::Run()
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");

	Config Config;
	TextDocument textDocument;

	SetTargetFPS(Config.GetInt("fps", 120));
	textDocument.OpenTextDocument(textFilePath, TextBuffer);

	Font font = GetFontDefault();
	font.baseSize = 20;
	InputController inputController;
	Cursor cursor(0, 0, 30, TextBuffer, font);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLANK);

		inputController.HandleInput(TextBuffer, cursor);
		cursor.UpdateBlink();
		DrawTextBuffer(font);
		cursor.Render();

		EndDrawing();
	}

	textDocument.SaveTextDocument(textFilePath, TextBuffer);
	CloseWindow();
}
