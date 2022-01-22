
#include <iostream>
#include <time.h>

#include "raylib.h"

#include "game.hpp"
#include "plant.hpp"
#include "player.hpp"

std::vector<Plant> game::plant_collection;
std::vector<Event> game::event_collection;

Player player;

bool that_was_close = false;

void water_me(){
    DrawText("WATER ME, I'M DYING", 250 , 250 - 50 , 20, BLACK);  
}

void spawn_first_plant(){
    static bool ran = false;
    if (ran == false)
        Plant(2000, 1, 50, {250, 250});
    ran = true;
    DrawText("Hello! I'm a your new plant!", 250 , 250 - 50 , 20, BLACK);  
}

void player_speech_one(){
    DrawText("I wish I had a plant!", player.pos.x , player.pos.y - 50 , 20, BLACK);  
}

void game::init(){
    InitWindow(game::screen_width, game::screen_height, "PLANTS!");
    SetRandomSeed(time(0));
    player.load_texture();
    Event(std::chrono::milliseconds{500}, nullptr, player_speech_one, std::chrono::milliseconds{2000});
    Event(std::chrono::milliseconds{2500}, nullptr , spawn_first_plant, std::chrono::milliseconds{2000});
    Event(std::chrono::milliseconds{4500}, nullptr , water_me, std::chrono::milliseconds{10000});
    
}


Rectangle sink(){
    const int width = 150;
    const int height = 50;
    Rectangle sink = {game::screen_width / 2 - width / 2, game::screen_height - height, width, height};
    return sink;
}


void draw_that_was_close(){
    static int close_count = 0;

    if (that_was_close and close_count < 60 * 2)
    {
        DrawText("That was close!", game::screen_width/2 , 5 , 20, BLACK);
        close_count++;
    }
    else{
        close_count = 0;
        that_was_close = false;
    }
}

void game::draw(){

    BeginDrawing();

    ClearBackground(GRAY);

    DrawText(TextFormat("x:%f\ny:%f", GetMousePosition().x, GetMousePosition().y), 5 , 5 , 10, BLACK);

    for(Plant& plant: game::plant_collection)
    {
        plant.draw();
    }

    player.draw();

    DrawRectangleRec(sink(), DARKBLUE);

    draw_that_was_close();

    event_draw_manager();

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



Event::Event(std::chrono::milliseconds time_to_event, std::function<void()> _init_cb, std::function<void()> _draw_cb, std::chrono::milliseconds duration)
{
    start_time = std::chrono::steady_clock::now() + time_to_event;
    end_time = start_time + duration;
    init_cb = _init_cb;
    draw_cb = _draw_cb;
    if(game::event_collection.empty())
        id = 1;
    else{
        id = game::event_collection.back().id + 1;
    }
    game::event_collection.push_back(*this);
}


void game::event_draw_manager(){

    auto time_now = std::chrono::steady_clock::now();
    for (auto event: event_collection)
    {
        if (event.end_time < time_now)
        {
            event_collection.erase(std::remove(event_collection.begin(), event_collection.end(), event), event_collection.end());
            return;
        }
        if (event.start_time < time_now && event.draw_cb != nullptr)
            event.draw_cb();  
    }
}


bool operator==(const Event & lhs, const Event & rhs)
{
    return lhs.id == rhs.id;
}

