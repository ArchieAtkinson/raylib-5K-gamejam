#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int screenWidth = 900;
int screenHeight = 900;

void UpdateDrawFrame(void);

int main()
{

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void)
{

    BeginDrawing();

    ClearBackground(GRAY);

    DrawText("Hello there", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}