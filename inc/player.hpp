#pragma once
#include "raylib.h"


class Player{
    public:
      Player();
      void load_texture();
      void update();
      void draw();
      Rectangle get_rec();

      int current_water;
      Vector2 pos;
      static const int max_water = 1000;
      static const int move_speed = 8;
      static const int water_per_tick = 25;
    private:
      void draw_water_bar();
      int speed;
      Texture2D player_texture;
};