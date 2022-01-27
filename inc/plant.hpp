#pragma once
#include "raylib.h"


class Plant {
    public:
        Plant(int _max_water, int _water_usage, Vector2 _pos);
        void draw();
        void update();
        void set_colour();
        bool water(int amount);
        Rectangle rec;
        Vector2 pos;
        void plant_speech(const char *speech);

        int id;
        static const int max_no_plants = 5;
 
      private:
        int max_water;
        int current_water;
        int water_usage;
        float size;
        Color colour;

        Texture2D tex_outline;
        Texture2D tex_colour;

        bool close_call;
        bool dying;
};

bool operator==(const Plant &lhs, const Plant &rhs);