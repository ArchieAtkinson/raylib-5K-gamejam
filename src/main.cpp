#include "raylib.h"

#include "game.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int main()
{
    game::init();
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(game::loop, 60, 1);
#else

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        game::loop();
    }

#endif

    CloseWindow();

    return 0;
}