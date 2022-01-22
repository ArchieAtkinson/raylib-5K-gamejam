
#include <iostream>
#include <time.h>

#include "raylib.h"

#include "game.hpp"
#include "plant.hpp"
#include "player.hpp"

std::vector<Plant> game::plant_collection;

Player player;

bool that_was_close = false;


void game::init(){
    InitWindow(game::screen_width, game::screen_height, "PLANTS!");

    while(Plant::max_no_plants > plant_collection.size())
    {
        Plant::generate_plant();
    }
    
    SetRandomSeed(time(0));

    Texture2D player_tex = LoadTexture("../resources/character_robot_talk.png");
    player = Player(player_tex);
}


Rectangle sink(){
    const int size = 100;
    Rectangle sink = {game::screen_width / 2 - size / 2, game::screen_height - size, size, size};
    return sink;
}


void game::draw(){
    static int close_count = 0;

    BeginDrawing();

    ClearBackground(GRAY);

    DrawText(TextFormat("x:%f\ny:%f", GetMousePosition().x, GetMousePosition().y), 5 , 5 , 10, BLACK);

    for(Plant& plant: game::plant_collection)
    {
        plant.draw();
    }

    player.draw();

    DrawRectangleRec(sink(), DARKBLUE);

    if (that_was_close and close_count < 60 * 2)
    {
        DrawText("That was close!", screen_width/2 , 5 , 20, BLACK);
        close_count++;
    }
    else{
        close_count = 0;
        that_was_close = false;
    }

    DrawFPS(screen_width - 100, 5);

    EndDrawing();

}


void game::update(){

    for(Plant& plant: game::plant_collection)
    {
        plant.update();
    }

    if(IsKeyDown(KEY_A) and player.pos.x > 0)
        player.pos.x -= 10;
    if(IsKeyDown(KEY_D) and player.pos.x < screen_width)
        player.pos.x += 10;
    if(IsKeyDown(KEY_W) and player.pos.y > 0)
        player.pos.y -= 10;
    if(IsKeyDown(KEY_S) and player.pos.y < screen_height)
        player.pos.y += 10;
    
    if(IsKeyDown(KEY_Q))
    {
        for(Plant& plant: game::plant_collection)
        {
            if(CheckCollisionRecs(player.get_rec(), plant.get_rec()))
            {
                if (player.current_water > 5)
                {
                    if (plant.water(5) < -400){
                        that_was_close = true;
                    }
                    player.current_water -= 5;
                }
            }
            break;
        }

        if(CheckCollisionRecs(player.get_rec(), sink()))
        {
            if (player.current_water < player.max_water)
            {
                player.current_water += 5;
            }
        }
    }

    player.update();
}

void game::loop(void)
{
    game::update();

    game::draw();
}
