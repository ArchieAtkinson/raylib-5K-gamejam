#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <list>

#include "plant.hpp"

class Event {
    
    public:
    Event(std::chrono::milliseconds time_to_event, std::function<void()> _init_cb, std::function<void()> _draw_cb, std::chrono::milliseconds duration);

    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;
    std::function<void()> init_cb;
    std::function<void()> draw_cb;
    int id;
};

namespace game {
    const int screen_width = 900;
    const int screen_height = 900;

    void init();
    void loop();
    void draw();
    void update();
    void random();
    void event_draw_manager();

    extern std::vector<Plant> plant_collection;
    extern std::vector<Event> event_collection;
}

