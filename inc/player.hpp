#pragma once
#include "raylib.h"


class Player{
    public:
      Player() = default;
      Player(Vector2 _pos);
      void load_texture();
      void update();
      void draw();
      void move(Vector2 dist);

      Rectangle rec;
      int current_water;
      Vector2 pos;
      static const int max_water = 1000;
      static const int move_speed = 8;
      static const int water_per_tick = 25;
    private:
      void draw_water_bar();
      Rectangle calc_rec(Vector2 _pos);
      int speed;
      Texture2D player_texture;
};