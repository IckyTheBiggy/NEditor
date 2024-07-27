#include "Editor.h"

void Editor::Run(const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window");

    SetTargetFPS(120);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLANK);
		EndDrawing();
	}

	CloseWindow();
}