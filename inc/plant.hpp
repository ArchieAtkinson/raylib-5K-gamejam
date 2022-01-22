#pragma once
#include "raylib.h"


class Plant {
    public:
        Plant(int _max_water, int _water_usage, float _size, Vector2 _pos);
        void draw();
        void update();
        void set_colour();
        int water(int amount);
        Rectangle get_rec();

      private:
        int max_water;
        int current_water;
        int water_usage;
        float size;
        Color colour;
        Vector2 pos;
        Rectangle rec;
};