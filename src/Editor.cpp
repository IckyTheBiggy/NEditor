#include "Editor.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const std::string textFilePath = "../test.txt";
std::vector<std::string> textBuffer;

void DrawTextBuffer(std::vector<std::string> textBuffer, const Font &font, int scrollOffset)
{	
	int windowHeight = GetScreenHeight();
	for (int i = 0; i < textBuffer.size(); i++)
	{
		int y = TEXT_PADDING + i * (font.baseSize + font.baseSize / 2) - scrollOffset;

		if (y >= -font.baseSize && y < windowHeight)
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
	int lineHeight = font.baseSize + font.baseSize / 2;
	int cursorY = cursor.GetY() * lineHeight;
	int viewportHeight = SCREEN_HEIGHT - 2 * TEXT_PADDING;

	float upperThresholdRatio = 0.2f;
	float lowerThresholdRation = 0.8f;

	int upperThreshold = static_cast<int>(viewportHeight * upperThresholdRatio);
	int lowerThreshold = static_cast<int>(viewportHeight * lowerThresholdRation);

	int cursorScreenY = cursorY - scrollOffset;

	if (cursorScreenY < upperThreshold)
	{
		scrollOffset = cursorY - upperThreshold;
	}

	else if (cursorScreenY > lowerThreshold)
	{
		scrollOffset = cursorY - lowerThreshold;
	}

	scrollOffset = std::max(0, scrollOffset);

	int totalTextHeight = textBuffer.size() * lineHeight;
	int maxScroll = std::max(0, totalTextHeight - viewportHeight);
	scrollOffset = std::min(scrollOffset, maxScroll);
}

int Editor::GetWindowWidth() const
{
	return GetScreenWidth();
}

int Editor::GetWindowHeight() const
{
	return GetScreenHeight();
}

void Editor::Run()
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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

		if (IsWindowResized())
		{
			UpdateScroll(cursor, font);
		}

		EndDrawing();
	}

	CloseWindow();
}
