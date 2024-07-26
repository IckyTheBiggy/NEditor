#include "Editor.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const std::string textFilePath = "../test.txt";
std::vector<std::string> textBuffer;

void DrawTextBuffer(std::vector<std::string> textBuffer, const Font &font)
{
	for (int i = 0; i < textBuffer.size(); i++)
	{
		DrawText(textBuffer[i].c_str(), TEXT_PADDING,
		         TEXT_PADDING + i * (font.baseSize + font.baseSize / 2),
		         font.baseSize, RAYWHITE);
	}
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
		DrawTextBuffer(textBuffer, font);
		cursor.Render();

		EndDrawing();
	}

	CloseWindow();
}
