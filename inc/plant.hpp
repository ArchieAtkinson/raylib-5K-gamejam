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
        Vector2 pos;
        static bool generate_plant();
        void plant_speech(const char *speech);
        int id;
        static const int max_no_plants = 5;

      private:
        int max_water;
        int current_water;
        int water_usage;
        float size;
        Color colour;
        Rectangle rec;
        
        bool close_call;
};

bool operator==(const Plant &lhs, const Plant &rhs);