#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <list>

#include "plant.hpp"
using namespace std::chrono_literals;
using milliseconds = std::chrono::milliseconds;

class Event {
    
    public:
      Event() = delete;
      Event(milliseconds time_to_event, std::function<void()> _func, milliseconds duration);
      Event(milliseconds time_to_event, std::function<void()> _func, milliseconds duration, milliseconds& time_to_end);

    
      std::chrono::time_point<std::chrono::steady_clock> start_time;
      std::chrono::time_point<std::chrono::steady_clock> end_time;
      std::function<void()> func;
      int id;
};

namespace game {
    const int screen_width = 900;
    const int screen_height = 900;
    extern bool game_over;

    void init();
    void loop();
    void draw();
    void update();
    void random();
    void event_runner();
    void intro_setup();

    extern std::vector<Plant> plant_collection;
    extern std::vector<Event> event_collection;
    extern std::vector<std::function<void()>> plant_queue;
}
