#include <iostream>

#include "plant.hpp"
#include "game.hpp"

Plant::Plant(int _max_water, int _water_usage, float _size, Vector2 _pos)
    : max_water{_max_water}, current_water{_max_water}, water_usage{_water_usage}, size{_size}, pos{_pos}, colour{GREEN}
    {
        rec = (Rectangle){pos.x - size / 2, pos.y - size / 2, size, size};

        game::plant_collection.push_back(*this);
    };

void Plant::draw()
{
    DrawRectangleRec(rec, colour);
    auto water_level = TextFormat("%d", current_water);
    DrawText(water_level, pos.x, pos.y, size/2, BLACK);
};


void Plant::update()
{
    if (current_water > - max_water/2)
        current_water -= water_usage;
    set_colour();

    if (CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        water(100);
}   

void Plant::set_colour()
{
    const unsigned char min_green = 50;
    const unsigned char max_green = 255;
    unsigned char green = static_cast<unsigned char>(game::map(current_water, static_cast<int>(-max_water / 2),  static_cast<int>(max_water * 1.5), min_green, max_green));

    const unsigned char min_red = 50;
    const unsigned char max_red = 0;

    unsigned char red = static_cast<unsigned char>(game::map(current_water,static_cast<int>(-max_water / 2),  static_cast<int>(max_water * 1.5), min_red, max_red));
    colour = (Color){red, green, 0, 255};
}

int Plant::water(int amount)
{
    if (current_water < max_water * 1.5)
        current_water += amount;
    return current_water;
}

Rectangle Plant::get_rec()
{
    return rec;
}