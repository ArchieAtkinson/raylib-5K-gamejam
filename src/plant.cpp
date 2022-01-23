#include <iostream>

#include "plant.hpp"
#include "game.hpp"

Plant::Plant(int _max_water, int _water_usage, float _size, Vector2 _pos)
    : max_water{_max_water}, current_water{_max_water}, water_usage{_water_usage}, size{_size}, pos{_pos}, colour{GREEN}
    {
        static int current_id = 0;
        close_call = false;
        id = current_id;
        current_id++;

        rec = (Rectangle){pos.x - size / 2, pos.y - size / 2, size, size};

        game::plant_collection.push_back(*this);
    };

void Plant::draw()
{
    DrawRectangleRec(rec, colour);
    auto water_level = TextFormat("%d", current_water);
    DrawText(water_level, pos.x, pos.y, size/5, BLACK);

    if (id != 0 and current_water < max_water * 0.2 )
    {
        plant_speech("WATER ME NOW!!");
    }

    if (current_water < max_water * 0.05 )
        close_call = true;
    if (close_call == true and current_water > max_water * 0.1 )
        {
            close_call = false;
            auto func = [this]() { this->plant_speech("That was close!"); };
            Event(0ms, func, 1000ms);
        }
};


void Plant::update()
{
    if (current_water > 0)
        current_water -= water_usage;
    set_colour();

    if (current_water <= 0){
        game::game_over = true;
        
    }
}   

unsigned char map(int x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Plant::set_colour()
{
    const unsigned char min_green = 50;
    const unsigned char max_green = 255;
    unsigned char green = map(current_water, 0,  max_water*1.05, min_green, max_green);

    const unsigned char min_red = 50;
    const unsigned char max_red = 0;

    unsigned char red = map(current_water, 0,  max_water*1.05,  min_red, max_red);
    colour = (Color){red, green, 0, 255};
}

int Plant::water(int amount)
{
    if (current_water < max_water)
    {
        current_water += amount;
    }
    return current_water;
}

Rectangle Plant::get_rec()
{
    return rec;
}

bool Plant::generate_plant()
{
    bool bad_pos = false;
    const int max_tries = 50;
    for (int i = 0; i < max_tries; i++)
    {
        float size = (float)GetRandomValue(20, 100);
        Vector2 pos = {static_cast<float>(GetRandomValue(size, game::screen_width - size)),
               static_cast<float>(GetRandomValue(size, game::screen_height - size))};
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
            return true;
        }
    }

    return false;
}

void Plant::plant_speech(const char* speech) {
    DrawText(speech, pos.x, pos.y - 50, 20, BLACK);
}

bool operator==(const Plant &lhs, const Plant &rhs)
{
    return lhs.id == rhs.id;
}
