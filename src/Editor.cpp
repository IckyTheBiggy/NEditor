#include "Editor.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

std::vector<std::string> TextBuffer = {""};

void HandleInput(Cursor& cursor)
{
    int key = GetCharPressed();

    while (key > 0)
    {
        if (key >= 32 && key <= 126)
        {
            std::string& currentLine = TextBuffer[cursor.GetY()];

            if (cursor.GetX() <= currentLine.size())
            {
                currentLine.insert(cursor.GetX(), 1, (char)key);
                cursor.MoveRight(currentLine.size());
            }
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (cursor.GetX() > 0)
        {
            TextBuffer[cursor.GetY()].erase(cursor.GetX() - 1, 1);
            cursor.MoveLeft();
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        TextBuffer.insert(TextBuffer.begin() + cursor.GetY() + 1, "");
        cursor.MoveDown(TextBuffer.size() - 1);
        cursor.SetX(0);
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        cursor.MoveLeft();
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        cursor.MoveRight(TextBuffer[cursor.GetY()].size());
    }

    if (IsKeyPressed(KEY_UP))
    {
        cursor.MoveUp();
        cursor.SetX(std::min(cursor.GetX(), (int)TextBuffer[cursor.GetY()].size()));
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        cursor.MoveDown(TextBuffer.size() - 1);
        cursor.SetX(std::min(cursor.GetX(), (int)TextBuffer[cursor.GetY()].size()));
    }
}

void DrawTextBuffer(const Font& font)
{
    for (int i = 0; i < TextBuffer.size(); i++)
    {
        DrawText(TextBuffer[i].c_str(), TEXT_PADDING, TEXT_PADDING + i * (font.baseSize + font.baseSize / 2), font.baseSize, RAYWHITE);
    }
}

void Editor::Run()
{
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");

    SetTargetFPS(120);

    Font font = GetFontDefault();
    font.baseSize = 10;
    Cursor cursor(0, 0, 30);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLANK);

        HandleInput(cursor);
        cursor.UpdateBlink();
        DrawTextBuffer(font);
        cursor.Render(TextBuffer, font);

        EndDrawing();
    }

    CloseWindow();
}