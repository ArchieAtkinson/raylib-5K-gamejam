#pragma once
#include <vector>
#include <random>


#include "plant.hpp"

namespace game {
    const int screen_width = 900;
    const int screen_height = 900;

    void init();
    void loop();
    void draw();
    void update();
    void random();

    extern std::vector<Plant> plant_collection;
}

