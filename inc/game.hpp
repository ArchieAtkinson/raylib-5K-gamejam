#pragma once
#include <vector>
#include <random>


#include "plant.hpp"

namespace game {
    const int screen_width = 900;
    const int screen_height = 900;
    const int max_no_plants = 10;

    void init();
    void loop();
    void draw();
    void update();
    void random();

    void generate_plant();

    int map(int x, int in_min, int in_max, int out_min, int out_max);

    extern std::vector<Plant> plant_collection;
}

