
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
    Plant(1000, 1, 100, (Vector2){100, 100});
    Plant(1000, 1, 100, (Vector2){200, 500});
    Plant(1000, 1, 100, (Vector2){600, 400});
    Plant(1000, 1, 100, (Vector2){200, 800});

    SetRandomSeed(time(0));

    Texture2D player_tex = LoadTexture("../resources/character_robot_talk.png");
    player = Player(player_tex);
}

void draw_water_bar()
{
    const int bar_width = 25;
    const int bar_length_max = 200;
    const int margin = 50;

    float water_per = (float)player.current_water / (float)player.max_water;
    std::cout << water_per << std::endl;
    int bar_length = water_per * 200;

    DrawRectangle(game::screen_width - margin, margin, bar_width, bar_length, BLUE);
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

    draw_water_bar();

    DrawRectangleRec(sink(), DARKBLUE);

    DrawRectangleLinesEx(player.get_rec(), 3, PINK);

    if (that_was_close and close_count < 60 * 2)
    {
        DrawText("That was close!", screen_width/2 , 5 , 20, BLACK);
        close_count++;
    }
    else{
        close_count = 0;
        that_was_close = false;
    }

    DrawFPS(screen_width - 50, 5);

    EndDrawing();

}


void game::update(){


    for(Plant& plant: game::plant_collection)
    {
        plant.update();
    }

    if(max_no_plants > plant_collection.size() and GetRandomValue(1,1) == 1)
    {
        // generate_plant();
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

int game::map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void game::generate_plant()
{

    bool bad_pos = false;
    const int max_tries = 50;
    for (int i = 0; i < max_tries; i++)
    {
        float size = (float)GetRandomValue(20, 100);
        Vector2 pos = {static_cast<float>(GetRandomValue(size, screen_width - size)),
               static_cast<float>(GetRandomValue(size, screen_height - size))};
        Rectangle rec = (Rectangle){pos.x - size / 2, pos.y - size / 2, size, size};
        for(Plant& plant: game::plant_collection)
        {            
            if (CheckCollisionRecs(plant.get_rec(), rec))
            {
                bad_pos = true;
                break;
            }
        }
        if (bad_pos == false){
            Plant(1000, 1, size, pos);
        }
    }
}