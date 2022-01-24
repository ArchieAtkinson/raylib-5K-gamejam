
#include <iostream>
#include <string>
#include <time.h>
#include <cmath>

#include "raylib.h"

#include "game.hpp"
#include "plant.hpp"
#include "player.hpp"

std::vector<Plant> game::plant_collection;
std::vector<Event> game::event_collection;

Player player;

int plant_rad = 300;

bool game::game_over = false;
bool game_start = false;
Rectangle game::sink;

Sound intro_music;

void game::init()
{
    InitWindow(game::screen_width, game::screen_height, "PLANTS!");
    SetRandomSeed(time(0));
    player.load_texture();
    sink_setup();

    InitAudioDevice();
    intro_music = LoadSound("../resources/intro2.wav");
    PlaySound(intro_music);
    SetMasterVolume(0);
}

void plant_speech(const char* speech) {
    Plant& plant = game::plant_collection[0];
    DrawText(speech, plant.pos.x, plant.pos.y - 50, 20, BLACK);
}

void game::intro_setup(){
    milliseconds time_to_end = 0ms;
    std::function<void()> func;
    Plant(10000, 1, 50, {pos_from_angle(plant_rad, 0)});

    func = []() { plant_speech("Oh, Hello there. I'm a your new plant!"); };
    Event(0ms, func, 3000ms, time_to_end);

    func = []() { plant_speech("It's nice to meet you."); };
    Event(time_to_end, func, 3000ms, time_to_end);  

    func = []() { plant_speech("I hope we can bring each other a lot of happiness"); };
    Event(time_to_end, func, 3000ms, time_to_end);

    func = []() { plant_speech("I'm pretty thirsty, could you water me please?"); };
    Event(time_to_end, func, 3000ms, time_to_end); 

    func = []() { plant_speech("Just come over to me with WASD and hold Q"); };
    Event(time_to_end, func, 3000ms, time_to_end); 
}

void game::loop(void)
{
    game::update();

    game::draw();
}

void first_water()
{
    static bool once = []()
    {
        milliseconds time_to_end = 0ms;
        std::function<void()> func;
        
        func = []() { plant_speech("Thank you"); };
        Event(1000ms, func, 3000ms, time_to_end); 

        func = []() { plant_speech("If you look to your right, you can see how much water you have"); };
        Event(time_to_end, func, 3000ms, time_to_end); 

        func = []() { plant_speech("To get more, just go to the sink at the botttom"); };
        Event(time_to_end, func, 3000ms, time_to_end); 

        func = []() { plant_speech("Just walk up to it and hold Q, just like you did to water me"); };
        Event(time_to_end, func, 3000ms, time_to_end); 

        return true;
    }();
}

void first_sink()
{
    static bool once = []()
    {
        milliseconds time_to_end = 0ms;
        std::function<void()> func;
        
        func = []() { plant_speech("Well done!"); };
        Event(3000ms, func, 3000ms, time_to_end); 

        func = []() { plant_speech("I constantly need water or else I'll die"); };
        Event(time_to_end, func, 5000ms, time_to_end); 

        func = []() { plant_speech("So make sure I don't run out and we will both be happy"); };
        Event(time_to_end, func, 5000ms, time_to_end); 

        func = []() { plant_speech("I've also got some friends who I would like you to meet"); };
        Event(time_to_end, func, 3000ms, time_to_end); 

        func = []() 
        {
            game::plant_collection.erase(std::remove( game::plant_collection.begin(),  game::plant_collection.end(), game::plant_collection[0]),
                                    game::plant_collection.end());
            Plant(4000, 2, 50, {game::pos_from_angle(plant_rad, 0)});
            Plant(5000, 3, 45, {game::pos_from_angle(plant_rad, 72)});
            Plant(2000, 1, 60, {game::pos_from_angle(plant_rad, 144)});
            Plant(3000, 1, 40, {game::pos_from_angle(plant_rad, 216)});
            Plant(6000, 5, 55, {game::pos_from_angle(plant_rad, 288)});
        }; 
        Event(time_to_end, func, 0ms, time_to_end); 

        func = []() 
        {
            for (Plant& plant: game::plant_collection)
                plant.plant_speech("WATER ME NOW!!");
            game_start = true;
        };
        Event(time_to_end, func, 2000ms, time_to_end);

        
        return true;
    }();

    
}


void game::update()
{
    for (Plant &plant : game::plant_collection)
    {
        plant.update();
    }
    
    if (IsKeyDown(KEY_A) and player.pos.x > 0)
        player.move((Vector2){-player.move_speed, 0});
    if (IsKeyDown(KEY_D) and player.pos.x < screen_width)
        player.move((Vector2){player.move_speed, 0});
    if (IsKeyDown(KEY_W) and player.pos.y > 0)
        player.move((Vector2){0, -player.move_speed});
    if (IsKeyDown(KEY_S) and player.pos.y < screen_height)
        player.move((Vector2){0, player.move_speed});

    if (IsKeyDown(KEY_Q))
    {
        
        for (Plant &plant : game::plant_collection)
        {

            
            if (CheckCollisionRecs(player.rec, scale_rec(plant.rec, 1.25)) and player.current_water > player.water_per_tick)
            {
                if (plant.water(player.water_per_tick))
                    player.current_water -= player.water_per_tick;
                first_water();
            }
            
        }
        if (CheckCollisionRecs(player.rec, scale_rec(sink, 1.25)) and player.current_water < player.max_water)
        {
            player.current_water += 50;
            first_sink();
        }
    }

    player.update();


    if (!IsSoundPlaying(intro_music))
        PlaySound(intro_music);

    if (game_over == true){
        DrawText("A plant has died,", 100, 100, 75, BLACK);
        DrawText("aren't you", 100, 200, 75, BLACK);
        DrawText("the worst", 100, 300, 75, BLACK);
        // game::plant_collection.clear();
        // game::event_collection.clear();
    }
}

void game::draw()
{
    
    BeginDrawing();

    ClearBackground(GRAY);

    DrawText(TextFormat("x:%f\ny:%f", GetMousePosition().x, GetMousePosition().y), 5, 5, 10, BLACK);

    for (Plant &plant : game::plant_collection)
    {
        plant.draw();
    }

    DrawRectangleRec(sink, DARKBLUE);
    player.draw();

    event_runner();

    DrawFPS(screen_width - 100, 5);

    if (game_start == true)
    {
        const static auto start_time = std::chrono::steady_clock::now();
        auto game_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time);
        auto game_time_f = std::chrono::duration<float>(game_time);
        auto time_str = TextFormat("%.3f\n", game_time_f.count());
        DrawText(time_str, screen_width/2, 10, 25, BLACK);
    }
        
    EndDrawing();
}



void game::sink_setup()
{
    const int width = 50;
    const int height = 50;
    Vector2 pos = {game::screen_width / 2, game::screen_height / 2};
    sink = {pos.x - width / 2, pos.y - height/2 , width, height};
}

Event::Event(milliseconds time_to_event, std::function<void()> _func, milliseconds duration)
{
    static int current_id = 0;
    id = current_id;
    current_id++;

    auto now = std::chrono::steady_clock::now();
    start_time = now + time_to_event;
    end_time = start_time + duration;
    func = _func;

    game::event_collection.push_back(*this);
}

Event::Event(milliseconds time_to_event, std::function<void()> _func, milliseconds duration, milliseconds& time_to_end)
{
    time_to_end = time_to_event + duration;
    Event(time_to_event, _func, duration);
}

void game::event_runner()
{

    auto time_now = std::chrono::steady_clock::now();
    for (auto event : event_collection)
    {
        if (event.start_time < time_now)
        {
            event.func();
        }
        if (event.end_time < time_now)
        {
            event_collection.erase(std::remove(event_collection.begin(), event_collection.end(), event),
                                   event_collection.end());
            return;
        }
    }
}

bool operator==(const Event &lhs, const Event &rhs)
{
    return lhs.id == rhs.id;
}

Rectangle game::scale_rec(const Rectangle& rec, float scale)
{
    Vector2 center = (Vector2){rec.x + rec.width / 2.0f, rec.y + rec.height / 2.0f};
    float height = rec.height * scale;
    float width = rec.width * scale;
    Rectangle new_rec = (Rectangle){center.x - width / 2.0f, center.y - width / 2.0f, width, height};
    return new_rec;
}

Vector2 game::pos_from_angle(float radius, double degrees)
{
    double radians = (degrees * 3.141592653589793238463) / 180.0;
    Vector2 centre = (Vector2){screen_width / 2.0f, screen_width / 2.0f};
    Vector2 out;
    out.x = static_cast<float>(radius * sin(radians) + centre.x);
    out.y = static_cast<float>(radius * -cos(radians) + centre.y);
    return out;
}